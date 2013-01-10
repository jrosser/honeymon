#include "decoder.h"

Decoder::Decoder()
{
    state = IDLE;
    raw = new QByteArray;

    //initialise statistics
    numInputBytes = 0;
    numCandidatePayloads = 0;
    numOverLengthMessages = 0;
    numLengthOdd = 0;
    numManchesterInvalid = 0;
    numCheckSumErrors = 0;
    numValidMessages = 0;
    numCollisions = 0;
    numSeventyBytes = 0;
}

void Decoder::inputBytes(QByteArray in)
{
    int size = in.size();
    numInputBytes += size;

    emit inputByteCount(numInputBytes);

    for(int i=0; i<size; i++) {
        decodeChar(in.at(i));
    }
}

void Decoder::decodeChar(char c)
{
    switch(state) {
      case IDLE:
        if (c=='3') {
          raw->append(c);
          state = HEAD1;
        }
        break;

      case HEAD1:
        if (c=='U') {
          raw->append(c);
          state = HEAD2;
        } else {
          raw->clear();
          state = IDLE;
        }
        break;

      case HEAD2:
        if (c=='S') {
          raw->append(c);
          state = PAYLOAD;
        } else {
          raw->clear();
          state = IDLE;
        }
        break;

      case PAYLOAD:
        //why do i receive 0x70 characters?
        //these seem spurious yet messages are valid with them removed
        if(c == 0x70) {
            numSeventyBytes++;
            emit seventyCount(numSeventyBytes);
            break;
        }

        //if two messages collide, we find the 0x33 0x55 0x53 pattern
        //in the middle of an existing payload
        if(c == '3') {
          raw->clear();
          raw->append(c);
          state = HEAD1;
          numCollisions++;
          emit collisionCount(numCollisions);
          break;
        }

        raw->append(c);
        if (c=='5') {
            numCandidatePayloads++;
            emit candidatePayloadCount(numCandidatePayloads);
            lengthCheck();
            raw->clear();
            state = IDLE;
        }
        break;

      default:
        raw->clear();
        state = IDLE;
    }
}

void Decoder::lengthCheck()
{
    if(raw->length() < 255) {
        manchesterDecode();
    } else {
        numOverLengthMessages++;
        emit overLengthMessageCount(numOverLengthMessages);
        emit consoleMessage(QString("Message too long - %1\n") .arg(raw->length()));
    }
}

char Decoder::manchesterLUT(char c)
{
    char val=-1;

    switch((unsigned char)c)
    {
      case 0xAA: val=0x00; break;
      case 0xA9: val=0x01; break;
      case 0xA6: val=0x02; break;
      case 0xA5: val=0x03; break;
      case 0x9A: val=0x04; break;
      case 0x99: val=0x05; break;
      case 0x96: val=0x06; break;
      case 0x95: val=0x07; break;
      case 0x6A: val=0x08; break;
      case 0x69: val=0x09; break;
      case 0x66: val=0x0A; break;
      case 0x65: val=0x0B; break;
      case 0x5A: val=0x0C; break;
      case 0x59: val=0x0D; break;
      case 0x56: val=0x0E; break;
      case 0x55: val=0x0F; break;
    }

    return val;
}

void Decoder::manchesterDecode()
{
    QByteArray mdecoded;
    QString msg;

    msg.append("RAW ");
    for(int i=0; i<raw->size(); i++) {
        msg.append(QString("%1 ") .arg(raw->at(i) & 0xFF, 2, 16, QChar('0')));
    }
    msg.append("\n");
    emit consoleMessage(msg);

    msg.clear();
    if(raw->length()%2 != 0) {
        numLengthOdd++;
        emit lengthOddCount(numLengthOdd);
        emit consoleMessage(QString("ERROR - packet length is not a multiple of 2\n"));
        return;
    }

    for(int i=3; i<raw->size()-1; i+=2) {
        char ms=manchesterLUT(raw->at(i));
        if(ms==-1) {
            numManchesterInvalid++;
            emit manchesterInvalidCount(numManchesterInvalid);
            emit consoleMessage(QString("Manchester decoding failed at %1 (ms) - 0x%2\n") .arg(i).arg(raw->at(i) & 0xFF, 2, 16));
            return;
        }

        char ls=manchesterLUT(raw->at(i+1));
        if(ls==-1) {
            numManchesterInvalid++;
            emit manchesterInvalidCount(numManchesterInvalid);
            emit consoleMessage(QString("Manchester decoding failed at %1 (ls) - 0x%2\n") .arg(i).arg(raw->at(i+1) & 0xFF, 2, 16));
            return;
        }

        char byte=(ms<<4) | ls;
        mdecoded.append(byte);
    }

    msg.append("DEC ");
    for(int i=0; i<mdecoded.size(); i++) {
        msg.append(QString("%1 ") .arg(mdecoded.at(i) & 0xFF, 2, 16, QChar('0')));
    }
    msg.append("\n");
    emit consoleMessage(msg);

    checksum(mdecoded);
}

void Decoder::checksum(QByteArray &in)
{
    int sum=0;

    for(int i=0; i<in.size(); i++)
        sum+=in.at(i);

    if((sum & 0xFF) == 0) {
        numValidMessages++;
        emit validMessageCount(numValidMessages);
        emit consoleMessage(QString("CHECKSUM - OK\n"));
        emit gotMessage(in);
        decodeHeader(in);
    } else {
        numCheckSumErrors++;
        emit checkSumErrorCount(numCheckSumErrors);
        emit consoleMessage(QString("CHECKSUM - FAIL\n"));
    }
}

void Decoder::writeLog(QByteArray &in, quint32 command)
{
    QString msg = QString("%1  ") .arg(command, 4, 16, QChar('0'));

    for(int i=0; i < (int)in.size(); i++) {
        msg.append(QString("%1 ") .arg(in.at(i) & 0xFF, 2, 16, QChar('0')));
    }

    emit logMessage(msg);
}

void Decoder::decodeHeader(QByteArray &in)
{
    bool id1_present=0;
    bool id2_present=0;
    bool ts_present=0;

    switch(in.at(0)) {
      case 0x18: //two addresses, no timestamp
        id1_present=1;
        id2_present=1;
        break;

      case 0x16: //one address and one timestamp
        id1_present=1;
        ts_present=1;
        break;

      case 0x14: //one address, no timestamp
        id1_present=1;
    }

    quint32 id1=0, id2=0;
    quint8 ts=0;

    //position we start parsing after the header byte
    qint32 index=1;

    if(id1_present) {
        id1  = (in.at(index) & 0xFF) << 16;
        id1 |= (in.at(index+1) & 0xFF) << 8;
        id1 |= (in.at(index+2) & 0xFF);
        index+=3;
    }

    if(id2_present) {
        id2  = (in.at(index) & 0xFF) << 16;
        id2 |= (in.at(index+1) & 0xFF) << 8;
        id2 |= (in.at(index+2) & 0xFF);
        index+=3;
    }

    if(ts_present) {
        ts = in.at(index++);
    }

    quint32 command = (in.at(index) & 0xFF) << 8 | (in.at(index+1) & 0xFF);
    index+=2;

    quint32 length = in.at(index++);

    writeLog(in, command);

    emit gotCommand(id1, id2, command);
    emit consoleMessage(QString("ID1=%1 ID2=%2 TS=%3 COMMAND=%4, LENGTH=%5\n")
                 .arg(id1, 6, 16, QChar('0')) .arg(id2, 6, 16, QChar('0'))
                 .arg(ts, 2, 16, QChar('0'))
                 .arg(command, 4, 16, QChar('0')) .arg(length));

    switch(command) {
      case 0x2309: //zone setpoint setting
        decode2309(id1, id2, length, index, in);
        break;
      case 0x3150: //heat demand timing
        decode3150(id1, id2, length, index, in);
        break;
      case 0x30C9: //zone temperature distribution
        decode30C9(id1, id2, length, index, in);
        break;
      case 0x2249: //programmer now/next setpoint
        decode2249(id1, length, index, in);
        break;
      case 0x1060: //unknown, but frequent
        decode1060(id1, id2, length, index, in);
        break;
      case 0x1100: //unknown
        decode1100(id1, length, index, in);
        break;
      case 0x0008: //unknown
        decode0008(id1, length, index, in);
        break;
      case 0x0009: //unknown
        decode0009(id1, length, index, in);
        break;
      case 0x000A: //hr80 parameters
        decode000A(id1, length, index, in);
        break;
      case 0x1F09: //unknown
        decode1F09(id1, length, index, in);
        break;
      case 0x3B00: //unknown
        decode3B00(id1, length, index, in);
        break;
      default:
        emit consoleMessage(QString("No decoder for command 0x%1\n") .arg(command, 4, 16));
    }

    emit consoleMessage(QString("\n"));
}

void Decoder::decode2309(quint32 id1, quint32 id2, quint32 length, quint32 i, QByteArray &in)
{
    //zone setpoint setting
    //a number of 3 byte sections
    for(int n=i; n<in.size()-1; n+=3) {
        quint32 zone = in.at(n) & 0xFF;
        quint32 temp_i = (in.at(n+1) & 0xFF) << 8 | (in.at(n+2) & 0xFF);
        float temp = (float)temp_i / 100.0;
        emit zoneSetpointSetting(id1, id2, zone, temp);
    }
}

void Decoder::decode3150(quint32 id1, quint32 id2, quint32 length, quint32 i, QByteArray &in)
{
    //heat demand
    quint32 zone = (in.at(i) & 0xFF);
    quint32 demand = (in.at(i+1) & 0xFF);
    emit heatDemand(id1, id2, zone, demand);
}

void Decoder::decode30C9(quint32 id1, quint32 id2, quint32 length, quint32 i, QByteArray &in)
{
    //zone temperature distribution
    //a number of 3 byte sections
    for(int n=i; n<in.size()-1; n+=3) {
        quint32 zone = in.at(n) & 0xFF;
        quint32 temp_i = (in.at(n+1) & 0xFF) << 8 | (in.at(n+2) & 0xFF);
        float temp = (float)temp_i / 100.0;
        emit zoneTempDistribution(id1, id2, zone, temp);
    }
}

void Decoder::decode2249(quint32 id1, quint32 length, quint32 i, QByteArray &in)
{
    //programmer now/next setpoint
    //a number of 7 byte sections, one for each zome
    for(int n=i; n<in.size()-1; n+=7) {
        quint32 zone = in.at(n) & 0xFF;
        quint32 tempNow_i = (in.at(n+1) & 0xFF) << 8 | (in.at(n+2) & 0xFF);
        quint32 tempNext_i = (in.at(n+3) & 0xFF) << 8 | (in.at(n+4) & 0xFF);
        float tempNow = (float)tempNow_i / 100.0;
        float tempNext = (float)tempNext_i / 100.0;
        quint32 countDown = (in.at(n+5) & 0xFF) << 8 | (in.at(n+6) & 0xFF);
        emit programmerNowNext(id1, zone, tempNow, tempNext, countDown);
    }
}

void Decoder::decode000A(quint32 id1, quint32 length, quint32 i, QByteArray &in)
{
    //HR80 parameters
    //a number of 6 byte sections, one for each zone
    for(int n=i; n<in.size()-1; n+=6) {
        quint32 zone = in.at(n) & 0xFF;
        quint32 flags = in.at(n+1) & 0xFF;
        quint32 tempMin_i = (in.at(n+2) & 0xFF) << 8 | (in.at(n+3) & 0xFF);
        quint32 tempMax_i = (in.at(n+4) & 0xFF) << 8 | (in.at(n+5) & 0xFF);
        float tempMin = (float)tempMin_i / 100.0;
        float tempMax = (float)tempMax_i / 100.0;
        emit hr80parameters(id1, zone, flags, tempMin, tempMax);
    }
}

void Decoder::decode1060(quint32 id1, quint32 id2, quint32 length, quint32 i, QByteArray &in)
{
   emit unknown1060(id1, id2, in);
}

void Decoder::decode1100(quint32 id1, quint32 length, quint32 i, QByteArray &in)
{
    emit unknown1100(id1, in);
}

void Decoder::decode0008(quint32 id1, quint32 length, quint32 i, QByteArray &in)
{
    emit unknown0008(id1, in);
}

void Decoder::decode0009(quint32 id1, quint32 length, quint32 i, QByteArray &in)
{
    emit unknown0009(id1, in);
}

void Decoder::decode1F09(quint32 id1, quint32 length, quint32 i, QByteArray &in)
{
    emit unknown1F09(id1, in);
}

void Decoder::decode3B00(quint32 id1, quint32 length, quint32 i, QByteArray &in)
{
    emit unknown3B00(id1, in);
}

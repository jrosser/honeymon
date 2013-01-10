#ifndef DECODER_H
#define DECODER_H

#include <QObject>

class Decoder : public QObject
{
Q_OBJECT

enum state_t { IDLE, HEAD1, HEAD2, PAYLOAD };

public:
    Decoder();

signals:
    //debugging to the console
    void consoleMessage(QString);

    //all valid messages
    void gotMessage(QByteArray);
    void gotCommand(quint32 id1, quint32 id2, quint32 command);

    //messages that we understand
    void zoneSetpointSetting(quint32 id1, quint32 id2, quint32 zone, float temp);
    void heatDemand(quint32 id1, quint32 id2, quint32 zone, quint32 demand);
    void zoneTempDistribution(quint32 id1, quint32 id2, quint32 zone, float temp);
    void programmerNowNext(quint32 id1, quint32 zone, float tempNow, float tempNext, quint32 countDown);
    void hr80parameters(quint32 id1, quint32 zone, quint32 flags, float tempMin, float tempMax);

    //things still to understand
    void unknown1060(quint32 id1, quint32 id2, QByteArray data);
    void unknown1100(quint32 id1, QByteArray data);
    void unknown0008(quint32 id1, QByteArray data);
    void unknown0009(quint32 id1, QByteArray data);
    void unknown1F09(quint32 id1, QByteArray data);
    void unknown3B00(quint32 id1, QByteArray data);

    //statistics
    void inputByteCount(quint32);
    void candidatePayloadCount(quint32);
    void overLengthMessageCount(quint32);
    void lengthOddCount(quint32);
    void manchesterInvalidCount(quint32);
    void checkSumErrorCount(quint32);
    void validMessageCount(quint32);
    void seventyCount(quint32);
    void collisionCount(quint32);

    void logMessage(QString);

public slots:
    void inputBytes(QByteArray in);

private:
    state_t state;
    QByteArray *raw;
    void decodeChar(char c);
    void lengthCheck();
    char manchesterLUT(char c);
    void manchesterDecode();
    void checksum(QByteArray &);
    void writeLog(QByteArray &, quint32 command);
    void decodeHeader(QByteArray &);
    void decode2309(quint32 id1, quint32 id2, quint32 length, quint32 i, QByteArray &in);
    void decode3150(quint32 id1, quint32 id2, quint32 length, quint32 i, QByteArray &in);
    void decode30C9(quint32 id1, quint32 id2, quint32 length, quint32 i, QByteArray &in);
    void decode2249(quint32 id1, quint32 length, quint32 i, QByteArray &in);
    void decode1060(quint32 id1, quint32 id2, quint32 length, quint32 index, QByteArray &in);
    void decode1100(quint32 id1, quint32 length, quint32 i, QByteArray &in);
    void decode0008(quint32 id1, quint32 length, quint32 i, QByteArray &in);
    void decode0009(quint32 id1, quint32 length, quint32 i, QByteArray &in);
    void decode000A(quint32 id1, quint32 length, quint32 i, QByteArray &in);
    void decode1F09(quint32 id1, quint32 length, quint32 i, QByteArray &in);
    void decode3B00(quint32 id1, quint32 length, quint32 i, QByteArray &in);

    //statistics
    quint32 numInputBytes;
    quint32 numCandidatePayloads;
    quint32 numOverLengthMessages;
    quint32 numLengthOdd;
    quint32 numManchesterInvalid;
    quint32 numCheckSumErrors;
    quint32 numValidMessages;
    quint32 numSeventyBytes;
    quint32 numCollisions;
};

#endif // DECODER_H

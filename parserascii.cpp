#include "parserascii.h"

ParserAscii::ParserAscii()
{
    state=IDLE;
}

//accept lines of text input messages of the form
//53 A9 6A A9 AA 5A 55 96 A9 AA 9A AA 95 69 A9 A5 A9 99 AA AA A6 AA A6 96 6A A9 55 35
void ParserAscii::inputBytes(QByteArray in)
{
    for(int i=0; i<in.size(); i++) {
        decodeChar(in.at(i));
    }
}

//reformat to binary equivalent
void ParserAscii::decodeChar(char c)
{
    static quint8 byte;

    //ignore any spaces
    if(c==' ')
        return;

    switch(state)
    {
        case IDLE:
            if(c=='5') state=HEAD;
            break;

        case HEAD:
            if(c=='3') state=PAYLOAD1;
            //prefix the message as it would have been
            //from the binary data
            data.append(0x33);
            data.append(0x55);
            data.append(0x53);
            break;

        case PAYLOAD1:
            //first character of payload
            byte = (c - '0') * 16;
            state = PAYLOAD2;
            break;

        case PAYLOAD2:
            //second character of payload
            byte += (c - '0');
            data.append(byte);

            //look for end of message
            if(byte==0x35) {
                emit outputBytes(data);
                data.clear();
                state=IDLE;
            } else {
                state=PAYLOAD1;
            }
            break;
    }
}

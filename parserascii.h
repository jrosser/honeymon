#ifndef PARSERASCII_H
#define PARSERASCII_H

#include "parser.h"

class ParserAscii : public Parser
{
    Q_OBJECT

    enum state_t { IDLE, HEAD, PAYLOAD1, PAYLOAD2 };

public:
    ParserAscii();

public slots:
    void inputBytes(QByteArray in);

private:
    quint8 charToInt(char c);
    void decodeChar(char c);
    state_t state;
    QByteArray data;
};

#endif // PARSERASCII_H

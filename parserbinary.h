#ifndef PARSERBINARY_H
#define PARSERBINARY_H

#include "parser.h"

class ParserBinary : public Parser
{
    Q_OBJECT

public:
    ParserBinary();

public slots:
    void inputBytes(QByteArray in) = 0;

signals:
    void outputBytes(QByteArray out);

};

#endif // PARSERBINARY_H

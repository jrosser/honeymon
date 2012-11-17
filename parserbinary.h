#ifndef PARSERBINARY_H
#define PARSERBINARY_H

#include "parser.h"

class ParserBinary : public Parser
{
    Q_OBJECT

public:
    ParserBinary();

public slots:
    void inputBytes(QByteArray in);

};

#endif // PARSERBINARY_H

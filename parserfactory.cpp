#include "parser.h"
#include "parserbinary.h"
#include "parserascii.h"

#include <QString>

Parser *ParserCreate(QString type)
{
    if(type.compare(QString("binary")) == 0)
        return new ParserBinary();

    if(type.compare(QString("ascii")) == 0)
        return new ParserAscii();

    return NULL;
}

#include "parser.h"
#include "parserbinary.h"

#include <QString>

Parser *ParserCreate(QString type)
{
    if(type.compare(QString("binary")) == 0)
        return new ParserBinary();

    return NULL;
}

#include "parserbinary.h"

ParserBinary::ParserBinary()
{
}

void ParserBinary::inputBytes(QByteArray in)
{
    //pass input bytes straight to decoder
    emit outputBytes(in);
}

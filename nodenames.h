#ifndef NODENAMES_H
#define NODENAMES_H

#include <QMap>
#include <QString>

class NodeNames
{
public:
    NodeNames();
    QString idToName(quint32 id);

private:
    QMap<quint32, QString> nameMap;
};

#endif // NODENAMES_H

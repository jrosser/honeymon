#include "commandmodel.h"
#include "nodenames.h"

#include <QFont>

CommandModel::CommandModel(QObject *parent) : QAbstractTableModel(parent)
{
}

int CommandModel::rowCount(const QModelIndex & /*parent*/) const
{
    return commandMap.count();
}

int CommandModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 4;
}

QVariant CommandModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        //get the value to display
        QMap<QString, record_t>::const_iterator i = commandMap.constBegin();
        int count=0;
        while (i != commandMap.constEnd()) {
            if(count==index.row()) {
                switch(index.column()) {
                case 0:
                {
                    quint32 id1=i.value().id1;
                    if(nn) return nn->idToName(id1);
                    return QString("%1") .arg(id1, 6, 16, QChar('0'));
                    break;
                }
                case 1:
                {
                    quint32 id2=i.value().id2;
                    if(id2 == 0) return QString("-");
                    if(nn) return nn->idToName(id2);
                    return QString("%1") .arg(id2, 6, 16, QChar('0'));
                    break;
                }
                case 2:
                    return QString("%1") .arg(i.value().command, 4, 16, QChar('0'));
                    break;
                case 3:
                    return QString("%1") .arg(i.value().count);
                default:
                    return QString("Unknown!");
                    break;
                }
            }

            ++i;
            ++count;
        }

    }
    if(role==Qt::FontRole)
    {
        QFont f;
        f.setPointSize(8);
        return f;
    }
    return QVariant();
}

QVariant CommandModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("ID1");
            case 1:
                return QString("ID2");
            case 2:
                return QString("Command");
            case 3:
                return QString("Count");
            }
        }
    }
    if(role==Qt::FontRole)
    {
        QFont f;
        f.setPointSize(8);
        return f;
    }
    return QVariant();
}

void CommandModel::newData(quint32 id1, quint32 id2, quint32 command)
{
    QString key = QString("%1:%2:%3")
            .arg(id1, 6, 16, QChar('0'))
            .arg(id2, 6, 16, QChar('0'))
            .arg(command, 4, 16, QChar('0'));

    record_t r;
    r.id1 = id1;
    r.id2 = id2;
    r.command = command;

    if(commandMap.contains(key))
        r.count = commandMap[key].count + 1;
    else
        r.count = 1;

    commandMap.insert(key, r);

    //for simplicity, request that the whole view is updated
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = (createIndex(commandMap.size(), 3));

    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);

}

void CommandModel::setNodeNameHelper(NodeNames *n)
{
    nn=n;
}

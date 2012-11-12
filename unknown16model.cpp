#include "unknown16model.h"
#include "nodenames.h"

#include <QFont>

Unknown16Model::Unknown16Model(QObject *parent) : QAbstractTableModel(parent)
{
}

int Unknown16Model::rowCount(const QModelIndex & /*parent*/) const
{
    return unknown16Map.count();
}

int Unknown16Model::columnCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

QVariant Unknown16Model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        //get the value to display
        QMap<QString, record_t>::const_iterator i = unknown16Map.constBegin();
        int count=0;
        while (i != unknown16Map.constEnd()) {
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
                    QString s;
                    //print the hex data
                    for(int j=0; j<i.value().data.size(); j++)
                        s.append(QString("%1 ") .arg(i.value().data.at(j) & 0xFF, 2, 16, QChar('0')));
                    return s;
                    break;
                }
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
        if(index.column() == 1) {
            QFont f("Monospace");
            f.setPointSize(8);
            f.setStyleHint(QFont::TypeWriter);
            return f;
        } else {
            QFont f;
            f.setPointSize(8);
            return f;
        }
    }
    return QVariant();
}

QVariant Unknown16Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("ID1");
                break;
            case 1:
                return QString("Data");
                break;
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

void Unknown16Model::newData(quint32 id1, QByteArray data)
{
    QString key = QString("%1")
            .arg(id1, 6, 16, QChar('0'));

    record_t r;
    r.id1 = id1;
    r.data = data;

    unknown16Map.insert(key, r);

    //for simplicity, request that the whole view is updated
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = (createIndex(unknown16Map.size(), 3));

    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);

}

void Unknown16Model::setNodeNameHelper(NodeNames *n)
{
    nn=n;
}

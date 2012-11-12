#include "unknown18model.h"
#include "nodenames.h"

#include <QFont>

Unknown18Model::Unknown18Model(QObject *parent) : QAbstractTableModel(parent)
{
}

int Unknown18Model::rowCount(const QModelIndex &) const
{
    return unknown18Map.count();
}

int Unknown18Model::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant Unknown18Model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        //get the value to display
        QMap<QString, record_t>::const_iterator i = unknown18Map.constBegin();
        int count=0;
        while (i != unknown18Map.constEnd()) {
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
                    if(nn) return nn->idToName(id2);
                    return QString("%1") .arg(id2, 6, 16, QChar('0'));
                    break;
                }
                case 2:
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
        if(index.column() == 2) {
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

QVariant Unknown18Model::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("ID2");
                break;
            case 2:
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

void Unknown18Model::newData(quint32 id1, quint32 id2, QByteArray data)
{
    QString key = QString("%1:%2")
            .arg(id1, 6, 16, QChar('0'))
            .arg(id2, 6, 16, QChar('0'));

    record_t r;
    r.id1 = id1;
    r.id2 = id2;
    r.data = data;

    unknown18Map.insert(key, r);

    //for simplicity, request that the whole view is updated
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = (createIndex(unknown18Map.size(), 3));

    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);

}

void Unknown18Model::setNodeNameHelper(NodeNames *n)
{
    nn=n;
}

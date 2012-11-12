#include "1060model.h"
#include "nodenames.h"

#include <QFont>

X1060Model::X1060Model(QObject *parent) : QAbstractTableModel(parent)
{
}

int X1060Model::rowCount(const QModelIndex & /*parent*/) const
{
   return x1060Map.count();
}

int X1060Model::columnCount(const QModelIndex & /*parent*/) const
{
   return 5;
}

QVariant X1060Model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        //get the value to display
        QMap<QString, record_t>::const_iterator i = x1060Map.constBegin();
        int count=0;
        while (i != x1060Map.constEnd()) {
            if(count==index.row()) {
                switch(index.column()) {
                  case 0:
                    if(nn) return nn->idToName(i.value().id1);
                    return QString("%1") .arg(i.value().id1, 6, 16, QChar('0'));
                    break;
                  case 1:
                    if(nn) return nn->idToName(i.value().id2);
                    return QString("%1") .arg(i.value().id2, 6, 16, QChar('0'));
                    break;
                  case 2:
                    return QString("%1") .arg(i.value().zone & 0xFF);
                    break;
                  case 3:
                    return QString("%1") .arg(i.value().one & 0xFF);
                    break;
                  case 4:
                    return QString("%1") .arg(i.value().two & 0xFF);
                    break;
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

QVariant X1060Model::headerData(int section, Qt::Orientation orientation, int role) const
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
                 return QString("Zone");
                 break;
             case 3:
                 return QString("1");
                 break;
             case 4:
                 return QString("2");
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

void X1060Model::newData(quint32 id1, quint32 id2, quint32 zone, quint32 one, quint32 two)
{
    QString key = QString("%1:%2:%3")
            .arg(id1, 6, 16, QChar('0'))
            .arg(id2, 6, 16, QChar('0'))
            .arg(zone);

    record_t r;
    r.id1 = id1;
    r.id2 = id2;
    r.zone = zone;
    r.one = one;
    r.two = two;

    x1060Map.insert(key, r);

    //for simplicity, request that the whole view is updated
     QModelIndex topLeft = createIndex(0,0);
     QModelIndex bottomRight = (createIndex(x1060Map.size(), 3));

     emit layoutChanged();
     emit dataChanged(topLeft, bottomRight);

}

void X1060Model::setNodeNameHelper(NodeNames *n)
{
    nn=n;
}

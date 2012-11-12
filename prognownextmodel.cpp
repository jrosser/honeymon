#include "prognownextmodel.h"
#include "nodenames.h"

#include <QFont>

ProgNowNextModel::ProgNowNextModel(QObject *parent) : QAbstractTableModel(parent)
{
    nn=NULL;
}

int ProgNowNextModel::rowCount(const QModelIndex &) const
{
   return temperatureMap.count();
}

int ProgNowNextModel::columnCount(const QModelIndex &) const
{
   return 5;
}

QVariant ProgNowNextModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        //get the value to display
        QMap<QString, record_t>::const_iterator i = temperatureMap.constBegin();
        int count=0;
        while (i != temperatureMap.constEnd()) {
            if(count==index.row()) {
                switch(index.column()) {
                  case 0:
                    {
                      quint32 id1 = i.value().id1;
                      if(nn) return nn->idToName(id1);
                      return QString("%1") .arg(id1, 6, 16, QChar('0'));
                    }
                    break;
                  case 1:
                    return i.value().zone;
                    break;
                  case 2:
                    return i.value().tempNow;
                    break;
                  case 3:
                    return i.value().tempNext;
                    break;
                  case 4:
                    return i.value().countDown;
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

QVariant ProgNowNextModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
     if (role == Qt::DisplayRole)
     {
         if (orientation == Qt::Horizontal) {
             switch (section)
             {
             case 0:
                 return QString("Prog");
             case 1:
                 return QString("Zone");
             case 2:
                 return QString("Now");
             case 3:
                 return QString("Next");
             case 4:
                 return QString("Countdown");
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

void ProgNowNextModel::newData(quint32 id1, quint32 zone, float tempNow, float tempNext, quint32 countDown)
{
    QString key = QString("%1:%2")
            .arg(id1, 6, 16, QChar('0'))
            .arg(zone);

    record_t r;
    r.id1 = id1;
    r.zone = zone;
    r.tempNow = tempNow;
    r.tempNext = tempNext;
    r.countDown = countDown;

    temperatureMap.insert(key, r);

    //for simplicity, request that the whole view is updated
     QModelIndex topLeft = createIndex(0,0);
     QModelIndex bottomRight = (createIndex(temperatureMap.size(), 4));
     emit layoutChanged();
     emit dataChanged(topLeft, bottomRight);
}

void ProgNowNextModel::setNodeNameHelper(NodeNames *n)
{
    nn=n;
}

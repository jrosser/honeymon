#include "tempmodel.h"
#include "nodenames.h"

#include <QFont>

TempModel::TempModel(QObject *parent) : QAbstractTableModel(parent)
{
    nn=NULL;
}

int TempModel::rowCount(const QModelIndex & /*parent*/) const
{
   return temperatureMap.count();
}

int TempModel::columnCount(const QModelIndex & /*parent*/) const
{
   return 3;
}

QVariant TempModel::data(const QModelIndex &index, int role) const
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
                  //The second ID is always equal to the first for HR80, or zero for a programmer
                  //Does not seem to be an interesting thing to display
                  //case 1:
                  //  {
                  //    quint32 id2 = i.value().id2;
                  //    if(nn) return nn->idToName(id2);
                  //    return QString("%1") .arg(id2, 6, 16, QChar('0'));
                  //  }
                  // break;
                  case 1:
                    return i.value().zone;
                    break;
                  case 2:
                    return QString("%1") .arg(i.value().temp);
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

QVariant TempModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
     if (role == Qt::DisplayRole)
     {
         if (orientation == Qt::Horizontal) {
             switch (section)
             {
             case 0:
                 return QString("Sensor");
             case 1:
                 return QString("Zone");
             case 2:
                 return QString("Temp");
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

void TempModel::newData(quint32 id1, quint32 id2, quint32 zone, float temp)
{
    QString key = QString("%1:%2:%3")
            .arg(id1, 6, 16, QChar('0'))
            .arg(id2, 6, 16, QChar('0'))
            .arg(zone);

    record_t r;
    r.id1 = id1;
    r.id2 = id2;
    r.zone = zone;
    r.temp = temp;

    temperatureMap.insert(key, r);

    //for simplicity, request that the whole view is updated
     QModelIndex topLeft = createIndex(0,0);
     QModelIndex bottomRight = (createIndex(temperatureMap.size(), 4));
     emit layoutChanged();
     emit dataChanged(topLeft, bottomRight);
}

void TempModel::setNodeNameHelper(NodeNames *n)
{
    nn=n;
}

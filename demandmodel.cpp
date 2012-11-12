#include "demandmodel.h"
#include "nodenames.h"

#include <QFont>

DemandModel::DemandModel(QObject *parent) : QAbstractTableModel(parent)
{
}

int DemandModel::rowCount(const QModelIndex &) const
{
    return demandMap.count();
}

int DemandModel::columnCount(const QModelIndex &) const
{
    return 4;
}

QVariant DemandModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        //get the value to display
        QMap<QString, record_t>::const_iterator i = demandMap.constBegin();
        int count=0;
        while (i != demandMap.constEnd()) {
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
                    return QString("%1") .arg(i.value().zone);
                    break;
                case 3:
                    return QString("%1") .arg(i.value().demand);
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

QVariant DemandModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Valve");
                break;
            case 1:
                return QString("Set By");
                break;
            case 2:
                return QString("Zone");
                break;
            case 3:
                return QString("Demand");
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

void DemandModel::newData(quint32 id1, quint32 id2, quint32 zone, quint32 demand)
{
    QString key = QString("%1:%2")
            .arg(id1, 6, 16, QChar('0'))
            .arg(id2, 6, 16, QChar('0'));

    record_t r;
    r.id1 = id1;
    r.id2 = id2;
    r.zone = zone;
    r.demand = demand;

    demandMap.insert(key, r);

    //for simplicity, request that the whole view is updated
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = (createIndex(demandMap.size(), 3));

    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);

}

void DemandModel::setNodeNameHelper(NodeNames *n)
{
    nn=n;
}

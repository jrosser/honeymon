#include "messagemodel.h"
#include "nodenames.h"

#include <QFont>

MessageModel::MessageModel(QObject *parent) : QAbstractTableModel(parent)
{
}

int MessageModel::rowCount(const QModelIndex &) const
{
    return messageList.count();
}

int MessageModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant MessageModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        //get the value to display
        QList<record_t>::const_iterator i = messageList.constBegin();
        int count=0;
        while (i != messageList.constEnd()) {
            if(count==index.row()) {
                switch(index.column()) {
                case 0:
                    return i->time.toString();
                    break;
                case 1:
                {
                    QString s;
                    //print the hex data
                    for(int j=0; j<i->data.size(); j++)
                        s.append(QString("%1 ") .arg(i->data.at(j) & 0xFF, 2, 16, QChar('0')));
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

QVariant MessageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Time");
            case 1:
                return QString("Message");
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

void MessageModel::newData(QByteArray data)
{
    record_t r;
    r.time = QTime::currentTime();
    r.data = data;

    messageList.append(r);

    //for simplicity, request that the whole view is updated
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = (createIndex(messageList.size(), 3));

    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);

}

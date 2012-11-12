#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QAbstractTableModel>

#include <QTime>

class MessageModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MessageModel(QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public slots:
    void newData(QByteArray in);

private:

    struct record_t {
      QTime time;
      QByteArray data;
    };

    QList<record_t> messageList;
};

#endif // MESSAGEMODEL_H

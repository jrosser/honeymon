#ifndef UNKNOWN18MODEL_H
#define UNKNOWN18MODEL_H

#include <QAbstractTableModel>

class NodeNames;

class Unknown18Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    Unknown18Model(QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setNodeNameHelper(NodeNames *n);

public slots:
    void newData(quint32 id0, quint32 id1, QByteArray data);

private:

    struct record_t {
      quint32 id1;
      quint32 id2;
      quint32 zone;
      QByteArray data;
    };

    NodeNames *nn;
    QMap<QString, record_t> unknown18Map;
};

#endif // UNKNOWN18MODEL_H

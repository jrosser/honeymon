#ifndef UNKNOWN16MODEL_H
#define UNKNOWN16MODEL_H

#include <QAbstractTableModel>

class NodeNames;

class Unknown16Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    Unknown16Model(QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setNodeNameHelper(NodeNames *n);

public slots:
    void newData(quint32 id0, QByteArray data);

private:

    struct record_t {
      quint32 id1;
      QByteArray data;
    };

    NodeNames *nn;
    QMap<QString, record_t> unknown16Map;
};

#endif // UNKNOWN16MODEL_H

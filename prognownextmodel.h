#ifndef PROGNOWNEXTMODEL_H
#define PROGNOWNEXTMODEL_H

#include <QAbstractTableModel>

class NodeNames;

class ProgNowNextModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ProgNowNextModel(QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setNodeNameHelper(NodeNames *n);

public slots:
    void newData(quint32 id1, quint32 zone, float tempNow, float tempNext, quint32 countDown);

private:

    struct record_t {
      quint32 id1;
      quint32 zone;
      float tempNow;
      float tempNext;
      quint32 countDown;
    };

    NodeNames *nn;
    QMap<QString, record_t> temperatureMap;
};

#endif // SETPOINTMODEL_H

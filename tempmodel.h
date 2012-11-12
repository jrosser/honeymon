#ifndef TEMPMODEL_H
#define TEMPMODEL_H

#include <QAbstractTableModel>

class NodeNames;

class TempModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TempModel(QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setNodeNameHelper(NodeNames *n);

public slots:
    void newData(quint32 id0, quint32 id1, quint32 zone, float temp);

private:

    struct record_t {
      quint32 id1;
      quint32 id2;
      quint32 zone;
      float temp;
    };

    NodeNames *nn;
    QMap<QString, record_t> temperatureMap;
};

#endif // TEMPMODEL_H

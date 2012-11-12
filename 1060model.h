#ifndef X1060MODEL_H
#define X1060MODEL_H

#include <QAbstractTableModel>

class NodeNames;

class X1060Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    X1060Model(QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setNodeNameHelper(NodeNames *n);

public slots:
    void newData(quint32 id0, quint32 id1, quint32 one, quint32 two, quint32 three);

private:

    struct record_t {
      quint32 id1;
      quint32 id2;
      quint32 zone;
      quint32 one;
      quint32 two;
    };

    NodeNames *nn;
    QMap<QString, record_t> x1060Map;
};

#endif // X1060MODEL_H

#ifndef TEMPERATURESTAB_H
#define TEMPERATURESTAB_H

#include <QWidget>

class QTableView;
class QAbstractTableModel;

class TemperaturesTab : public QWidget
{
    Q_OBJECT
public:
    explicit TemperaturesTab(QWidget *parent = 0);

    void setMeasuredTempsModel(QAbstractTableModel *);
    void setSetpointsModel(QAbstractTableModel *);
    void setDemandsModel(QAbstractTableModel *);
    void setProgNowNextModel(QAbstractTableModel *);

private:
    QTableView *measuredTempsTable;
    QTableView *setpointsTable;
    QTableView *demandsTable;
    QTableView *nowNextTable;
};

#endif // TEMPERATURESTAB_H

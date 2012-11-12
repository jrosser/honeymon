#ifndef UNKNOWNTAB_H
#define UNKNOWNTAB_H

#include <QWidget>

class QTableView;
class QAbstractTableModel;

class UnknownTab : public QWidget
{
    Q_OBJECT
public:
    explicit UnknownTab(QWidget *parent = 0);

    void set1060Model(QAbstractTableModel *);
    void set1100Model(QAbstractTableModel *);
    void set0008Model(QAbstractTableModel *);
    void set0009Model(QAbstractTableModel *);
    void set1F09Model(QAbstractTableModel *);
    void set3B00Model(QAbstractTableModel *);

private:
    QTableView *x1060Table;
    QTableView *x1100Table;
    QTableView *x0008Table;
    QTableView *x0009Table;
    QTableView *x1F09Table;
    QTableView *x3B00Table;
};

#endif // UNKNOWNTAB_H

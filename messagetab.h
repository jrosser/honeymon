#ifndef MESSAGETAB_H
#define MESSAGETAB_H

#include <QWidget>

class QTableView;
class QAbstractTableModel;

class MessageTab : public QWidget
{
    Q_OBJECT
public:
    explicit MessageTab(QWidget *parent = 0);

    void setMessageCountersModel(QAbstractTableModel *);
    void setMessageLogModel(QAbstractTableModel *);

private:
    QTableView *messageCountersTable;
    QTableView *messageLogTable;
};

#endif // MESSAGETAB_H

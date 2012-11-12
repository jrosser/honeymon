#include "messagetab.h"

#include <QtGui>

MessageTab::MessageTab(QWidget *parent) :
    QWidget(parent)
{
    //overall grid layout
    QGridLayout *overallLayout = new QGridLayout();

    //group box for message log
    QGroupBox *messageLogGroup = new QGroupBox("Message log");
    QVBoxLayout *messageLogLayout = new QVBoxLayout();
    messageLogTable = new QTableView();
    messageLogTable->verticalHeader()->hide();
    messageLogLayout->addWidget(messageLogTable);
    messageLogGroup->setLayout(messageLogLayout);
    overallLayout->addWidget(messageLogGroup, 0, 0, 1, 1);

    //group box for message counters
    QGroupBox *messageCountersGroup = new QGroupBox("Message counters");
    QVBoxLayout *messageCountersLayout = new QVBoxLayout();
    messageCountersTable = new QTableView();
    messageCountersTable->verticalHeader()->hide();
    messageCountersLayout->addWidget(messageCountersTable);
    messageCountersGroup->setLayout(messageCountersLayout);
    overallLayout->addWidget(messageCountersGroup, 0, 1, 1, 1);

    //set the layout for the whole tab
    this->setLayout(overallLayout);
}

void MessageTab::setMessageCountersModel(QAbstractTableModel *m)
{
    messageCountersTable->setModel(m);
    connect(m, SIGNAL(layoutChanged()), messageCountersTable, SLOT(resizeColumnsToContents()));
    connect(m, SIGNAL(layoutChanged()), messageCountersTable, SLOT(resizeRowsToContents()));
    messageCountersTable->resizeColumnsToContents();
}

void MessageTab::setMessageLogModel(QAbstractTableModel *m)
{
    messageLogTable->setModel(m);
    connect(m, SIGNAL(layoutChanged()), messageLogTable, SLOT(resizeColumnsToContents()));
    connect(m, SIGNAL(layoutChanged()), messageLogTable, SLOT(resizeRowsToContents()));
    messageLogTable->resizeColumnsToContents();
}

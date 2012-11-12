#include "temperaturestab.h"

#include <QtGui>

TemperaturesTab::TemperaturesTab(QWidget *parent) :
    QWidget(parent)
{
    //overall grid layout
    QGridLayout *overallLayout = new QGridLayout();

    //group box for measured temperatures
    QGroupBox *measuredTempsGroup = new QGroupBox("Measured Temperatures 0x30c9");
    QVBoxLayout *measuredTempsLayout = new QVBoxLayout();
    measuredTempsTable = new QTableView();
    measuredTempsTable->verticalHeader()->hide();
    measuredTempsLayout->addWidget(measuredTempsTable);
    measuredTempsGroup->setLayout(measuredTempsLayout);
    overallLayout->addWidget(measuredTempsGroup, 0, 0, 1, 1);

    //group box for setpoints
    QGroupBox *setpointsGroup = new QGroupBox("Setpoints 0x2309");
    QVBoxLayout *setpointsLayout = new QVBoxLayout();
    setpointsTable = new QTableView();
    setpointsTable->verticalHeader()->hide();
    setpointsLayout->addWidget(setpointsTable);
    setpointsGroup->setLayout(setpointsLayout);
    overallLayout->addWidget(setpointsGroup, 0, 1, 1, 1);

    //group box for TRV demands
    QGroupBox *demandsGroup = new QGroupBox("Demand 0x3150");
    QVBoxLayout *demandsLayout = new QVBoxLayout();
    demandsTable = new QTableView();
    demandsTable->verticalHeader()->hide();
    demandsLayout->addWidget(demandsTable);
    demandsGroup->setLayout(demandsLayout);
    overallLayout->addWidget(demandsGroup, 0, 2, 2, 1);

    //group box for programmer now / next info
    QGroupBox *nowNextGroup = new QGroupBox("Programmer now/next 0x2249");
    QVBoxLayout *nowNextLayout = new QVBoxLayout();
    nowNextTable = new QTableView();
    nowNextTable->verticalHeader()->hide();
    nowNextLayout->addWidget(nowNextTable);
    nowNextGroup->setLayout(nowNextLayout);
    overallLayout->addWidget(nowNextGroup, 0, 3, 1, 1);

    //set the layout for the whole tab
    this->setLayout(overallLayout);
}

void TemperaturesTab::setMeasuredTempsModel(QAbstractTableModel *m)
{
    measuredTempsTable->setModel(m);
    connect(m, SIGNAL(layoutChanged()), measuredTempsTable, SLOT(resizeColumnsToContents()));
    connect(m, SIGNAL(layoutChanged()), measuredTempsTable, SLOT(resizeRowsToContents()));
    measuredTempsTable->resizeColumnsToContents();
}

void TemperaturesTab::setSetpointsModel(QAbstractTableModel *m)
{
    setpointsTable->setModel(m);
    connect(m, SIGNAL(layoutChanged()), setpointsTable, SLOT(resizeColumnsToContents()));
    connect(m, SIGNAL(layoutChanged()), setpointsTable, SLOT(resizeRowsToContents()));
    setpointsTable->resizeColumnsToContents();
}

void TemperaturesTab::setDemandsModel(QAbstractTableModel *m)
{
    demandsTable->setModel(m);
    connect(m, SIGNAL(layoutChanged()), demandsTable, SLOT(resizeColumnsToContents()));
    connect(m, SIGNAL(layoutChanged()), demandsTable, SLOT(resizeRowsToContents()));
    demandsTable->resizeColumnsToContents();
}

void TemperaturesTab::setProgNowNextModel(QAbstractTableModel *m)
{
    nowNextTable->setModel(m);
    connect(m, SIGNAL(layoutChanged()), nowNextTable, SLOT(resizeColumnsToContents()));
    connect(m, SIGNAL(layoutChanged()), nowNextTable, SLOT(resizeRowsToContents()));
    nowNextTable->resizeColumnsToContents();
}

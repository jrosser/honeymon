#include "unknowntab.h"

#include <QtGui>

#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>

UnknownTab::UnknownTab(QWidget *parent) :
    QWidget(parent)
{
    //overall grid layout
    QGridLayout *overallLayout = new QGridLayout();

    void unknown1060(quint32 id1, quint32 id2, quint32 one, quint32 two, quint32 three);
    void unknown1100(quint32 id1, QByteArray data);
    void unknown0008(quint32 id1, QByteArray data);
    void unknown0009(quint32 id1, QByteArray data);
    void unknown1F09(quint32 id1, QByteArray data);
    void unknown3B00(quint32 id1, QByteArray data);

    QGroupBox *x1060Group = new QGroupBox("0x1060");
    QVBoxLayout *x1060Layout = new QVBoxLayout();
    x1060Table = new QTableView();
    x1060Table->verticalHeader()->hide();
    x1060Layout->addWidget(x1060Table);
    x1060Group->setLayout(x1060Layout);
    overallLayout->addWidget(x1060Group, 0, 0, 1, 1);

    QGroupBox *x1100Group = new QGroupBox("0x1100");
    QVBoxLayout *x1100Layout = new QVBoxLayout();
    x1100Table = new QTableView();
    x1100Table->verticalHeader()->hide();
    x1100Layout->addWidget(x1100Table);
    x1100Group->setLayout(x1100Layout);
    overallLayout->addWidget(x1100Group, 0, 1, 1, 1);

    QGroupBox *x0008Group = new QGroupBox("0x0008");
    QVBoxLayout *x0008Layout = new QVBoxLayout();
    x0008Table = new QTableView();
    x0008Table->verticalHeader()->hide();
    x0008Layout->addWidget(x0008Table);
    x0008Group->setLayout(x0008Layout);
    overallLayout->addWidget(x0008Group, 0, 2, 1, 1);

    QGroupBox *x0009Group = new QGroupBox("0x0009");
    QVBoxLayout *x0009Layout = new QVBoxLayout();
    x0009Table = new QTableView();
    x0009Table->verticalHeader()->hide();
    x0009Layout->addWidget(x0009Table);
    x0009Group->setLayout(x0009Layout);
    overallLayout->addWidget(x0009Group, 1, 0, 1, 1);

    QGroupBox *x1F09Group = new QGroupBox("0x1F09");
    QVBoxLayout *x1F09Layout = new QVBoxLayout();
    x1F09Table = new QTableView();
    x1F09Table->verticalHeader()->hide();
    x1F09Layout->addWidget(x1F09Table);
    x1F09Group->setLayout(x1F09Layout);
    overallLayout->addWidget(x1F09Group, 1, 1, 1, 1);

    QGroupBox *x3B00Group = new QGroupBox("0x3B00");
    QVBoxLayout *x3B00Layout = new QVBoxLayout();
    x3B00Table = new QTableView();
    x3B00Table->verticalHeader()->hide();
    x3B00Layout->addWidget(x3B00Table);
    x3B00Group->setLayout(x3B00Layout);
    overallLayout->addWidget(x3B00Group, 1, 2, 1, 1);

    //set the layout for the whole tab
    this->setLayout(overallLayout);
}

void UnknownTab::set1060Model(QAbstractTableModel *m)
{
    x1060Table->setModel(m);
    connect(m, SIGNAL(layoutChanged()), x1060Table, SLOT(resizeColumnsToContents()));
    connect(m, SIGNAL(layoutChanged()), x1060Table, SLOT(resizeRowsToContents()));
    x1060Table->resizeColumnsToContents();
}

void UnknownTab::set1100Model(QAbstractTableModel *m)
{
    x1100Table->setModel(m);
    connect(m, SIGNAL(layoutChanged()), x1100Table, SLOT(resizeColumnsToContents()));
    connect(m, SIGNAL(layoutChanged()), x1100Table, SLOT(resizeRowsToContents()));
    x1100Table->resizeColumnsToContents();
}

void UnknownTab::set0008Model(QAbstractTableModel *m)
{
    x0008Table->setModel(m);
    connect(m, SIGNAL(layoutChanged()), x0008Table, SLOT(resizeColumnsToContents()));
    connect(m, SIGNAL(layoutChanged()), x0008Table, SLOT(resizeRowsToContents()));
    x0008Table->resizeColumnsToContents();
}

void UnknownTab::set0009Model(QAbstractTableModel *m)
{
    x0009Table->setModel(m);
    connect(m, SIGNAL(layoutChanged()), x0009Table, SLOT(resizeColumnsToContents()));
    connect(m, SIGNAL(layoutChanged()), x0009Table, SLOT(resizeRowsToContents()));
    x0009Table->resizeColumnsToContents();
}

void UnknownTab::set1F09Model(QAbstractTableModel *m)
{
    x1F09Table->setModel(m);
    connect(m, SIGNAL(layoutChanged()), x1F09Table, SLOT(resizeColumnsToContents()));
    connect(m, SIGNAL(layoutChanged()), x1F09Table, SLOT(resizeRowsToContents()));
    x1F09Table->resizeColumnsToContents();
}

void UnknownTab::set3B00Model(QAbstractTableModel *m)
{
    x3B00Table->setModel(m);
    connect(m, SIGNAL(layoutChanged()), x3B00Table, SLOT(resizeColumnsToContents()));
    connect(m, SIGNAL(layoutChanged()), x3B00Table, SLOT(resizeRowsToContents()));
    x3B00Table->resizeColumnsToContents();
}

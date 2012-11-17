#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"

#include <QMessageBox>
#include <QTableView>
#include <QHBoxLayout>
#include <QtAddOnSerialPort/serialport.h>
#include <QtNetwork>

#include "nodenames.h"
#include "decoder.h"

#include "tempmodel.h"
#include "setpointmodel.h"
#include "demandmodel.h"
#include "commandmodel.h"
#include "prognownextmodel.h"
#include "unknown18model.h"
#include "unknown16model.h"
#include "messagemodel.h"

#include "decodertab.h"
#include "temperaturestab.h"
#include "unknowntab.h"
#include "messagetab.h"

#include "parserfactory.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    console = new Console;
    console->setEnabled(false);

    tabs = new QTabWidget();
    setCentralWidget(tabs);

    serial = new SerialPort(this);
    settings = new SettingsDialog;

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);
    ui->actionAscii->setEnabled(true);
    ui->actionBinary->setEnabled(true);

    nodeNames = new NodeNames();
    logFile = new LogFile();

    decoder = new Decoder();
    connect(decoder, SIGNAL(logMessage(QString)), logFile, SLOT(add(QString)));

    tempDistModel = new TempModel(this);
    tempDistModel->setNodeNameHelper(nodeNames);

    zoneSetpointModel = new SetpointModel(this);
    zoneSetpointModel->setNodeNameHelper(nodeNames);

    demandModel = new DemandModel(this);
    demandModel->setNodeNameHelper(nodeNames);

    commandModel = new CommandModel(this);
    commandModel->setNodeNameHelper(nodeNames);

    nowNextModel = new ProgNowNextModel(this);
    nowNextModel->setNodeNameHelper(nodeNames);

    unknown1060Model = new Unknown18Model(this);
    unknown1060Model->setNodeNameHelper(nodeNames);

    unknown1100Model = new Unknown16Model(this);
    unknown1100Model->setNodeNameHelper(nodeNames);

    unknown0008Model = new Unknown16Model(this);
    unknown0008Model->setNodeNameHelper(nodeNames);

    unknown0009Model = new Unknown16Model(this);
    unknown0009Model->setNodeNameHelper(nodeNames);

    unknown1F09Model = new Unknown16Model(this);
    unknown1F09Model->setNodeNameHelper(nodeNames);

    unknown3B00Model = new Unknown16Model(this);
    unknown3B00Model->setNodeNameHelper(nodeNames);

    messageModel = new MessageModel(this);

    MessageTab *messageTab = new MessageTab();
    messageTab->setMessageCountersModel(commandModel);
    messageTab->setMessageLogModel(messageModel);
    tabs->addTab(messageTab, "Messages");

    TemperaturesTab *temperaturesTab = new TemperaturesTab();
    temperaturesTab->setMeasuredTempsModel(tempDistModel);
    temperaturesTab->setSetpointsModel(zoneSetpointModel);
    temperaturesTab->setDemandsModel(demandModel);
    temperaturesTab->setProgNowNextModel(nowNextModel);

    tabs->addTab(temperaturesTab, "Temperatures");

    UnknownTab *unknownTab = new UnknownTab();
    unknownTab->set0008Model(unknown0008Model);
    unknownTab->set0009Model(unknown0009Model);
    unknownTab->set1060Model(unknown1060Model);
    unknownTab->set1100Model(unknown1100Model);
    unknownTab->set1F09Model(unknown1F09Model);
    unknownTab->set3B00Model(unknown3B00Model);
    tabs->addTab(unknownTab, "Unknown messages");

    DecoderTab *decoderTab = new DecoderTab();
    tabs->addTab(decoderTab, "Decoder");

    tabs->addTab(console, "Console");

    initActionsConnections();

    parser=NULL;
    setBinaryParser();

    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));

    connect(decoder, SIGNAL(consoleMessage(QString)), this, SLOT(message(QString)));
    connect(decoder, SIGNAL(gotMessage(QByteArray)), messageModel, SLOT(newData(QByteArray)));

    //connect decoded messages to tables
    connect(decoder, SIGNAL(zoneTempDistribution(quint32,quint32,quint32,float)), tempDistModel, SLOT(newData(quint32,quint32,quint32,float)));
    connect(decoder, SIGNAL(zoneSetpointSetting(quint32,quint32,quint32,float)), zoneSetpointModel, SLOT(newData(quint32,quint32,quint32,float)));
    connect(decoder, SIGNAL(heatDemand(quint32,quint32,quint32,quint32)), demandModel, SLOT(newData(quint32, quint32, quint32, quint32)));
    connect(decoder, SIGNAL(gotCommand(quint32,quint32,quint32)), commandModel, SLOT(newData(quint32,quint32,quint32)));
    connect(decoder, SIGNAL(programmerNowNext(quint32,quint32,float,float,quint32)), nowNextModel, SLOT(newData(quint32, quint32, float, float, quint32)));

    //connect unknown messages to tables
    connect(decoder, SIGNAL(unknown1060(quint32,quint32,QByteArray)), unknown1060Model, SLOT(newData(quint32,quint32,QByteArray)));
    connect(decoder, SIGNAL(unknown1100(quint32,QByteArray)), unknown1100Model, SLOT(newData(quint32,QByteArray)));
    connect(decoder, SIGNAL(unknown0008(quint32,QByteArray)), unknown0008Model, SLOT(newData(quint32,QByteArray)));
    connect(decoder, SIGNAL(unknown0009(quint32,QByteArray)), unknown0009Model, SLOT(newData(quint32,QByteArray)));
    connect(decoder, SIGNAL(unknown1F09(quint32,QByteArray)), unknown1F09Model, SLOT(newData(quint32,QByteArray)));
    connect(decoder, SIGNAL(unknown3B00(quint32,QByteArray)), unknown3B00Model, SLOT(newData(quint32,QByteArray)));

    //connect decoder stats to decoder tab
    connect(decoder, SIGNAL(inputByteCount(quint32)), decoderTab, SLOT(inputByteCount(quint32)));
    connect(decoder, SIGNAL(candidatePayloadCount(quint32)), decoderTab, SLOT(candidatePayloadCount(quint32)));
    connect(decoder, SIGNAL(overLengthMessageCount(quint32)), decoderTab, SLOT(overLengthMessageCount(quint32)));
    connect(decoder, SIGNAL(lengthOddCount(quint32)), decoderTab, SLOT(lengthOddCount(quint32)));
    connect(decoder, SIGNAL(manchesterInvalidCount(quint32)), decoderTab, SLOT(manchesterInvalidCount(quint32)));
    connect(decoder, SIGNAL(validMessageCount(quint32)), decoderTab, SLOT(validMessageCount(quint32)));

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(8888, QUdpSocket::ShareAddress);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void MainWindow::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        if(parser)
            parser->inputBytes(datagram);
    }
}

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}

void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPort(p.name);
    if (serial->open(QIODevice::ReadWrite)) {
        if (serial->setRate(p.rate)
                && serial->setDataBits(p.dataBits)
                && serial->setParity(p.parity)
                && serial->setStopBits(p.stopBits)
                && serial->setFlowControl(p.flowControl)) {

            console->setEnabled(true);
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionConfigure->setEnabled(false);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

        } else {
            serial->close();
            QMessageBox::critical(this, tr("Error"),
                                  tr("Can't configure the serial port: %1,\n"
                                     "error code: %2")
                                  .arg(p.name).arg(serial->error()));

            ui->statusBar->showMessage(tr("Open error"));
        }
    } else {
        QMessageBox::critical(this, tr("Error"),
                              tr("Can't opened the serial port: %1,\n"
                                 "error code: %2")
                              .arg(p.name).arg(serial->error()));

        ui->statusBar->showMessage(tr("Configure error"));
    }
}

void MainWindow::closeSerialPort()
{
    serial->close();
    console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("CMZone/Evotouch montior"),
                       tr("This program decodes some of the messages in a "
                          "Honeywell CMZone/Evotouch heating control system and "
                          "displays the key system state"));
}

void MainWindow::readData()
{
    QByteArray data = serial->readAll();

    if(parser)
        parser->inputBytes(data);
}

void MainWindow::message(QString s)
{
    console->putData(s.toAscii());
}

void MainWindow::setParser(QString type)
{
    if(parser)
    {
        parser->disconnect();
        delete parser;
        parser=NULL;
    }

    qDebug() << "setting parser to " << type;
    parser=ParserCreate(type);
    connect(parser, SIGNAL(outputBytes(QByteArray)), decoder, SLOT(inputBytes(QByteArray)));
}

void MainWindow::setAsciiParser()
{
    setParser(QString("ascii"));
    ui->actionAscii->setChecked(true);
    ui->actionBinary->setChecked(false);
}

void MainWindow::setBinaryParser()
{
    setParser(QString("binary"));
    ui->actionAscii->setChecked(false);
    ui->actionBinary->setChecked(true);
}

void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionAscii, SIGNAL(triggered()), this, SLOT(setAsciiParser()));
    connect(ui->actionBinary, SIGNAL(triggered()), this, SLOT(setBinaryParser()));
}

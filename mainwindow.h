#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Decoder;
class NodeNames;
class TempModel;
class DemandModel;
class CommandModel;
class SetpointModel;
class ProgNowNextModel;
class X1060Model;
class Unknown16Model;
class Unknown18Model;
class MessageModel;
class Parser;

#include "logfile.h"

class QTableView;
class QHBoxLayout;
class QUdpSocket;

namespace Ui {
class MainWindow;
}

class Console;
class SettingsDialog;

class QSerialPort;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void closing();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void readData();
    void message(QString);
    void readPendingDatagrams();
    void setParser(QString);
    void setAsciiParser();
    void setBinaryParser();
private:
    void initActionsConnections();

private:
    Ui::MainWindow *ui;
    Console *console;
    SettingsDialog *settings;
    QSerialPort *serial;
    QUdpSocket *udpSocket;

    QTabWidget *tabs;

    LogFile *logFile;

    NodeNames *nodeNames;
    Decoder *decoder;
    Parser *parser;

    TempModel *tempDistModel;
    SetpointModel *zoneSetpointModel;
    DemandModel *demandModel;
    CommandModel *commandModel;
    ProgNowNextModel *nowNextModel;
    MessageModel *messageModel;

    Unknown18Model *unknown1060Model;
    Unknown16Model *unknown1100Model;
    Unknown16Model *unknown0008Model;
    Unknown16Model *unknown0009Model;
    Unknown16Model *unknown1F09Model;
    Unknown16Model *unknown3B00Model;
};

#endif // MAINWINDOW_H

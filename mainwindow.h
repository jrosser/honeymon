#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtAddOnSerialPort/serialport-global.h>

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

QT_BEGIN_NAMESPACE_SERIALPORT
class SerialPort;
QT_END_NAMESPACE_SERIALPORT

QT_USE_NAMESPACE_SERIALPORT

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void readData();
    void message(QString);
    void readPendingDatagrams();

private:
    void initActionsConnections();

private:
    Ui::MainWindow *ui;
    Console *console;
    SettingsDialog *settings;
    SerialPort *serial;
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

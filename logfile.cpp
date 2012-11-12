#include "logfile.h"

#include <QString>
#include <QFile>
#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>

LogFile::LogFile()
{
    out=NULL;

    log = new QFile("/var/tmp/cmzone.log");

    if (log->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
      out = new QTextStream(log);
    } else {
      //qDebug() << "Error opening log file '" << fileName << "'. All debug output redirected to console.";
    }
}

LogFile::~LogFile()
{
    log->close();
}

void LogFile::add(QString msg)
{
    QString debugdate = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");

    if(out)
        (*out) << debugdate << " " << msg << endl;
    else
        qDebug() << debugdate << " " << msg << endl;
}

#ifndef LOGFILE_H
#define LOGFILE_H

#include <QObject>

class QTextStream;
class QFile;

class LogFile : public QObject
{
Q_OBJECT

public:
    LogFile();
    ~LogFile();

public slots:
    void add(QString);

private:
    QFile *log;
    QTextStream *out;
};

#endif // LOGFILE_H

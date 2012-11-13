#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QByteArray>

//base class for parsers

class Parser : public QObject
{
    Q_OBJECT;

public slots:
    virtual void inputBytes(QByteArray in) = 0;

signals:
    void outputBytes(QByteArray);
};

#endif // PARSER_H

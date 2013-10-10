#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QObject::connect(&a, SIGNAL(aboutToQuit()), &w, SLOT(closing()));
    return a.exec();
}

#include "mainwindow.h"

#include <QApplication>
#include "registerTools.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    registerTools();

    MainWindow w;
    w.show();
    return a.exec();
}

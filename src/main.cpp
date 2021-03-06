#include "mainwindow.h"

#include <QApplication>
#include "registerTools.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon{":/icon/appIcon.ico"});

    registerTools();

    MainWindow w;
    w.show();
    return a.exec();
}

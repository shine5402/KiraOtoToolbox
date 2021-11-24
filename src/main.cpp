#include "mainwindow.h"

#include <QApplication>
#include "initFuncs.h"
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon{":/icon/appIcon.ico"});

    a.setApplicationName("KiraOtoToolBox");

    QSplashScreen splashScr(QPixmap(":/splashscr", "png"));
    splashScr.show();

    registerTools();

    MainWindow w;
    w.show();

    splashScr.finish(&w);
    return a.exec();
}

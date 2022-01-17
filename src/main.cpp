#include "mainwindow.h"

#include <QApplication>
#include "initFuncs.h"
#include <QSplashScreen>
#include <QLocale>
#include <kira/darkmode.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle("Fusion");
    auto arg = a.arguments();

    a.setWindowIcon(QIcon{":/icon/appIcon.ico"});

    a.setOrganizationName("KiraTools");
    a.setApplicationName("KiraOtoToolBox");
    DarkMode::setCurrentPaletteToApp();

    QSplashScreen splashScr(QPixmap(":/splashscr", "png"));
    splashScr.show();

    registerTools();

    MainWindow w;
    w.show();

    splashScr.finish(&w);
    return a.exec();
}

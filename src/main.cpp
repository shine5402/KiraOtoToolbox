#include <QApplication>
#include <QFontDatabase>
#include <QLocale>
#include "InitFuncs.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto arg = a.arguments();

    a.setOrganizationName("KiraTools");
    a.setApplicationName("KiraOtoToolBox");

    registerTools();

    MainWindow w;
    w.show();

    // For js tool
    QFontDatabase::addApplicationFont(":/font/JetBrainsMono-Regular.ttf");

    return a.exec();
}

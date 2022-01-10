#include <kira/darkmode.h>
#include <QSettings>
#include <QApplication>
#include <QPalette>
#include <QWidget>
#include <QStyleFactory>
#include <QStyle>
#include <QMenu>

namespace DarkMode {
    static QMenu* darkModeMenu = nullptr;
    static QAction* lightAction = nullptr;
    static QAction* darkAction = nullptr;
    void setCurrentActionChecked();
}

DarkMode::Mode DarkMode::getCurrentMode()
{
    QSettings settings;
    return settings.value("darkMode", LIGHT).value<Mode>();
}

void DarkMode::setCurrentMode(Mode mode)
{
    QSettings settings;
    settings.setValue("darkMode", mode);
}

void DarkMode::setCurrentPaletteToApp()
{
    QApplication::setPalette(getPaletteFor(getCurrentMode()));
}

QPalette DarkMode::getPaletteFor(Mode mode)
{
    if (mode == DARK){
        QColor darkGray(53, 53, 53);
        QColor gray(128, 128, 128);
        QColor black(25, 25, 25);
        QColor blue(42, 130, 218);

        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, darkGray);
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, black);
        darkPalette.setColor(QPalette::AlternateBase, darkGray);
        darkPalette.setColor(QPalette::ToolTipBase, blue);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, darkGray);
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::Link, blue);
        darkPalette.setColor(QPalette::Highlight, blue);
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);

        darkPalette.setColor(QPalette::Active, QPalette::Button, gray.darker());
        darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, gray);
        darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, gray);
        darkPalette.setColor(QPalette::Disabled, QPalette::Text, gray);
        darkPalette.setColor(QPalette::Disabled, QPalette::Light, darkGray);
        return darkPalette;
    }
    else
    {
        auto lightPalette = QStyleFactory::create("fusion")->standardPalette();
        lightPalette.setColor(QPalette::Window, QColor(250,250,250));
        return lightPalette;
    }
}

QMenu* DarkMode::getDarkModeSettingMenu()
{
    if (darkModeMenu)
        return darkModeMenu;

    darkModeMenu = new QMenu(QCoreApplication::translate("DarkMode","UI Theme"));

    lightAction = darkModeMenu->addAction(QCoreApplication::translate("DarkMode", "Light"));
    lightAction->setCheckable(true);
    QObject::connect(lightAction, &QAction::triggered, [](){
        setCurrentMode(LIGHT);
        setCurrentPaletteToApp();
        setCurrentActionChecked();
    });
    darkAction = darkModeMenu->addAction(QCoreApplication::translate("DarkMode", "Dark"));
    darkAction->setCheckable(true);
    QObject::connect(darkAction, &QAction::triggered, [](){
        setCurrentMode(DARK);
        setCurrentPaletteToApp();
        setCurrentActionChecked();
    });
    setCurrentActionChecked();

    return darkModeMenu;
}

void DarkMode::setCurrentActionChecked(){
    lightAction->setChecked(getCurrentMode() == LIGHT);
    darkAction->setChecked(getCurrentMode() == DARK);
}

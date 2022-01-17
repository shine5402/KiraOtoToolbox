#ifndef KIRA_DARKMODE_H
#define KIRA_DARKMODE_H
#include <QMetaType>
#include <QObject>

class QMenu;
class QPalette;
class QWidget;

/*
 * Don't forget to set Application's name and organization
 * as it is needed by store settings.
 * And don't forget to call:
 * QApplication::setStyle("Fusion");
 * DarkMode::setCurrentPaletteToApp();
 * You should setApplicaitonName and setOrganizationName before call setCurrentPaletteToApp().
 */
namespace DarkMode {
    Q_NAMESPACE
    enum Mode {
        LIGHT, DARK
    };
    Q_ENUM_NS(Mode)

    Mode getCurrentMode();
    void setCurrentMode(Mode mode);
    void setCurrentPaletteToApp();

    QPalette getPaletteFor(Mode mode);
    QMenu* getDarkModeSettingMenu();

    class Observer : public QObject {
        Q_OBJECT
    private:
        explicit Observer(QObject* parent) : QObject(parent){};

    signals:
        ///Emitted when setCurrentPaletteToApp being called, as you should change assets that time
        void darkModeChanged(DarkMode::Mode curr);

    friend Observer* getObserver();
    };

    Observer* getObserver();
}

#endif // KIRA_DARKMODE_H

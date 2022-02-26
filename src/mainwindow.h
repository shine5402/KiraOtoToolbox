#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <kira/darkmode.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Translation;
class QButtonGroup;
class QGroupBox;

namespace UpdateChecker {
    class GithubReleaseChecker;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createToolSelectorUI();

private:
    Ui::MainWindow *ui;
    QMenu* i18nMenu = nullptr;
    QVector<QObject*> toolButtonsLayoutResources;

    void setArgInfoBlock();

    QMenu* createHelpMenu();

    UpdateChecker::GithubReleaseChecker* updateChecker;

private slots:
    void showAboutDialog();
    void fitUIToDarkMode(DarkMode::Mode curr);
    // QWidget interface
protected:
    void changeEvent(QEvent*) override;
};
#ifndef NDEBUG

#endif

#endif // MAINWINDOW_H

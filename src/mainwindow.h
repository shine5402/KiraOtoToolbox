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

private slots:
    void showAboutDialog();
    void showDonationPage();
    void showUpdatePage();
    void showFeedbackPage();
    void fitLogoToDarkMode(DarkMode::Mode curr);
    // QWidget interface
protected:
    void changeEvent(QEvent*) override;
};
#ifndef NDEBUG

#endif

#endif // MAINWINDOW_H

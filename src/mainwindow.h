#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void exit();
    void showAboutDialog();
    void showAboutQtDialog();
#ifndef NDEBUG
    void on_debugButton_clicked();
#endif
    void processButtonClicked(int id);
};
#ifndef NDEBUG

#endif

#endif // MAINWINDOW_H

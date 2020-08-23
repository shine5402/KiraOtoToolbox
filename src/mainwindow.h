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

    void on_duplicateRemoveButton_clicked();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
    void on_overlapBatchSetButton_clicked();
#ifndef NDEBUG
    void on_debugButton_clicked();
#endif
    void on_affixRemoveButton_clicked();
    void on_affixAddPushButton_clicked();
};
#ifndef NDEBUG
#include "toolBase/tooldialogadapter.h"
class EmptyToolDialogAdapter : public ToolDialogAdapter{
    Q_OBJECT
public:
    EmptyToolDialogAdapter(QObject* parent = nullptr) : ToolDialogAdapter(parent){

    }
    void setupSpecificUIWidgets(QLayout *rootLayout) override;;
    QString getWindowTitle() const override;
};
#endif

#endif // MAINWINDOW_H

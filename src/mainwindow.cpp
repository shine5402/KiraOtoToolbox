#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "removeduplicatedialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_duplicateRemoveButton_clicked()
{
    auto dialog = new RemoveDuplicateDialog(this);
    dialog->open();
}

void MainWindow::on_actionExit_triggered()
{
    qApp->exit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, tr("关于"), tr("由shine_5402开发。日后再说更多吧。"));
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, tr("关于 Qt"));
}

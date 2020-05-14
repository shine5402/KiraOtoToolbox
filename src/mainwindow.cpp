#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "removeduplicatedialog.h"

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

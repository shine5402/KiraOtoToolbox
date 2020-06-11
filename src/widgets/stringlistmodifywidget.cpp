#include "stringlistmodifywidget.h"
#include "ui_stringlistmodifywidget.h"

#include <QInputDialog>
#include <QMessageBox>

StringListModifyWidget::StringListModifyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StringListModifyWidget)
{
    ui->setupUi(this);
    ui->listView->setModel(model);
    connect(ui->addButton, &QPushButton::clicked, this, &StringListModifyWidget::addRow);
    connect(ui->deleteButton, &QPushButton::clicked, this, &StringListModifyWidget::deleteCurrentRow);
}

StringListModifyWidget::~StringListModifyWidget()
{
    delete ui;
}

QStringList StringListModifyWidget::getData() const
{
    return model->stringList();
}

void StringListModifyWidget::setData(const QStringList& value)
{
    model->setStringList(value);
}

void StringListModifyWidget::addRow()
{
    model->insertRow(model->rowCount() - 1);
}

void StringListModifyWidget::deleteCurrentRow()
{
    model->removeRow(ui->listView->currentIndex().row());
}

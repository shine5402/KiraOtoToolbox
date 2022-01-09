#include <kira/widgets/stringlistmodifywidget.h>
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
    connect(ui->multiLineEditButton, &QPushButton::clicked, this, &StringListModifyWidget::openMultiLineEdit);
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
    emit dataModified();
}

void StringListModifyWidget::addRow()
{
    bool ok;
    auto str = QInputDialog::getText(this, tr("Input new value"), tr("Input the new string to append"), QLineEdit::Normal, {}, &ok);
    if (ok)
    {
        if (str.isEmpty())
        {
            QMessageBox::critical(this, tr("Input is empty"),tr("Input is empty. The list remains unchanged."));
            return;
        }
        model->insertRow(model->rowCount());
        model->setData(model->index(model->rowCount() - 1), str);
        emit dataModified();
    }
}

void StringListModifyWidget::deleteCurrentRow()
{
    model->removeRow(ui->listView->currentIndex().row());
    emit dataModified();
}

void StringListModifyWidget::openMultiLineEdit()
{
    bool ok = false;
    auto result = QInputDialog::getMultiLineText(this, tr("Input data"), tr("Input what to apply for the list. One data per line."), getData().join("\n"), &ok);
    if (ok)
    {
        setData(result.split("\n",Qt::SkipEmptyParts));
        emit dataModified();
    }
}

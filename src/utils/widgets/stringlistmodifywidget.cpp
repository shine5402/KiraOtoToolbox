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
    auto str = QInputDialog::getText(this, tr("输入新值"), tr("输入要添加到列表的新字符串"), QLineEdit::Normal, {}, &ok);
    if (ok)
    {
        if (str.isEmpty())
        {
            QMessageBox::critical(this, tr("输入值为空"),tr("提供的输入是空的。列表不会做出更改。"));
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
    auto result = QInputDialog::getMultiLineText(this, tr("输入数据"), tr("请输入要应用于列表里的数据，一行一个。"), getData().join("\n"), &ok);
    if (ok)
    {
        setData(result.split("\n",Qt::SkipEmptyParts));
        emit dataModified();
    }
}

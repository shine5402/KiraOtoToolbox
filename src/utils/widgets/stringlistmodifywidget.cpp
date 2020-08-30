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


    bool ok;
#ifdef SHINE5402OTOBOX_TEST
    auto str = QString("TestAdd");
    ok = true;
#endif
#ifndef SHINE5402OTOBOX_TEST
    auto str = QInputDialog::getText(this, tr("输入新值"), tr("输入要添加到列表的新字符串"), QLineEdit::Normal, {}, &ok);
#endif
    if (ok)
    {
        if (str.isEmpty())
        {
#ifdef SHINE5402OTOBOX_TEST
            Q_ASSERT(false);
#endif
            QMessageBox::critical(this, tr("输入值为空"),tr("提供的输入是空的。列表不会做出更改。"));
            return;
        }
        model->insertRow(model->rowCount());
        model->setData(model->index(model->rowCount() - 1), str);
    }
}

void StringListModifyWidget::deleteCurrentRow()
{
    model->removeRow(ui->listView->currentIndex().row());
}

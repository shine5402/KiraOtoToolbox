#include "otofilemultipleloadwidget.h"
#include "ui_otofilemultipleloadwidget.h"

#include "../dialogs/showotolistdialog.h"
#include <QMessageBox>
#include <otofilereader.h>

OtoFileMultipleLoadWidget::OtoFileMultipleLoadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OtoFileMultipleLoadWidget)
{
    ui->setupUi(this);
    ui->otoFileTableView->setModel(model);
    connect(model, qOverload<>(&OtoFileMultipleLoadOtoFileListModel::dataChanged),
            this, &OtoFileMultipleLoadWidget::dataChanged);
    connect(ui->loadButton, &QPushButton::clicked, this, &OtoFileMultipleLoadWidget::appendOtoFile);
    connect(ui->removeButton, &QPushButton::clicked, this, &OtoFileMultipleLoadWidget::removeOtoFile);
    connect(ui->showContentButton, &QPushButton::clicked, this, &OtoFileMultipleLoadWidget::showOtoList);
}

OtoFileMultipleLoadWidget::~OtoFileMultipleLoadWidget()
{
    delete ui;
}

void OtoFileMultipleLoadWidget::reset()
{
    model->reset();
}


int OtoFileMultipleLoadWidget::count() const
{
    return model->rowCount();
}

QList<OtoEntryList> OtoFileMultipleLoadWidget::entryLists() const
{
    QList<OtoEntryList> result;

    auto datas = model->datas();
    for (const auto& data : datas){
        result.append(data.entryList);
    }

    return result;
}

QStringList OtoFileMultipleLoadWidget::fileNames() const
{
    QStringList result;

    auto datas = model->datas();
    for (const auto& data : datas){
        result.append(data.fileName);
    }

    return result;
}

void OtoFileMultipleLoadWidget::showOtoList()
{
    auto currentList = model->data(currentRow()).entryList;
    auto dialog = new ShowOtoListDialog(&currentList, this);
    dialog->open();
}

void OtoFileMultipleLoadWidget::appendOtoFile()
{
    auto fileName = ui->openFileNameEdit->fileName();

    if (!QFileInfo::exists(fileName)){
#ifdef SHINE5402OTOBOX_TEST
        Q_ASSERT(false);
#endif
        QMessageBox::critical(this, tr("文件不存在"), tr("您指定的文件不存在，请检查后再试。"));
        return;
    }

    if (fileNames().contains(fileName))
    {
#ifdef SHINE5402OTOBOX_TEST
        Q_ASSERT(false);
#endif
        QMessageBox::warning(this, tr("已经读取"), tr("您指定的文件已经被读取过了。"));
        return;
    }

    OtoFileReader reader(fileName);
    auto entryList = reader.getEntryList();

    model->addData(fileName, entryList);

    ui->openFileNameEdit->setFileName("");
    refreshButtonEnableState();
}

void OtoFileMultipleLoadWidget::removeOtoFile()
{
    if (model->rowCount() > 0){
        model->deleteData(currentRow());
        refreshButtonEnableState();
    }
}

int OtoFileMultipleLoadWidget::currentRow()
{
    return ui->otoFileTableView->currentIndex().row();
}

void OtoFileMultipleLoadWidget::refreshButtonEnableState()
{
    ui->removeButton->setEnabled(count() > 0);
    ui->showContentButton->setEnabled(count() > 0);
}

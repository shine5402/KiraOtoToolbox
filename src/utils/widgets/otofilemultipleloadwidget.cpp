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
    connect(model, qOverload<>(&OtoFileListModel::dataChanged),
            this, &OtoFileMultipleLoadWidget::dataChanged);
    connect(ui->loadButton, &QPushButton::clicked, this, &OtoFileMultipleLoadWidget::appendOtoFile);
    connect(ui->removeButton, &QPushButton::clicked, this, &OtoFileMultipleLoadWidget::removeOtoFile);
    connect(ui->showContentButton, &QPushButton::clicked, this, &OtoFileMultipleLoadWidget::showOtoList);
    connect(ui->otoFileTableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &OtoFileMultipleLoadWidget::onSelectionChanged);

    ui->openFileNameEdit->setMultipleMode(true);
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
    auto currentList = new OtoEntryList(model->data(currentRow()).entryList);
    auto dialog = new ShowOtoListDialog(currentList, this);
    dialog->open();
    connect(dialog, &QObject::destroyed, [currentList](){delete currentList;});
}

void OtoFileMultipleLoadWidget::appendOtoFile()
{
    auto fileNames = ui->openFileNameEdit->fileNames();

    for (auto fileName : fileNames){
        if (!QFileInfo::exists(fileName)){
#ifdef SHINE5402OTOBOX_TEST
            Q_ASSERT(false);
#endif
            QMessageBox::critical(this, tr("文件不存在"), tr("您指定的文件 %1 不存在，请检查后再试。").arg(fileName));
            return;
        }

        if (this->fileNames().contains(fileName))
        {
#ifdef SHINE5402OTOBOX_TEST
            Q_ASSERT(false);
#endif
            QMessageBox::warning(this, tr("已经读取"), tr("您指定的文件 %1 已经被读取过了。").arg(fileName));
            return;
        }

        OtoFileReader reader(fileName);
        auto entryList = reader.getEntryList();

        model->addData(fileName, entryList);
    }

    ui->openFileNameEdit->setFileName("");
    refreshButtonEnableState();

    constexpr auto COLUMN_OTO_FILENAME = 0;
    ui->otoFileTableView->resizeColumnToContents(COLUMN_OTO_FILENAME);
}

void OtoFileMultipleLoadWidget::removeOtoFile()
{
    if (model->rowCount() > 0){
        QSet<int> selectedRowsSet;
        for (auto index : ui->otoFileTableView->selectionModel()->selection().indexes()){
            selectedRowsSet.insert(index.row());
        }
        auto selectedRows = selectedRowsSet.values();
        std::sort(selectedRows.begin(), selectedRows.end(), std::greater<>());

        for (auto i : selectedRows){
            model->deleteData(i);
        }
    }
}

void OtoFileMultipleLoadWidget::onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    Q_UNUSED(deselected)
    ui->showContentButton->setEnabled(selected.count() <= 1);

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

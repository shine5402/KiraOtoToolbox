#include "otofilemultipleloadwidget.h"
#include "ui_otofilemultipleloadwidget.h"

#include "../dialogs/showotolistdialog.h"
#include <QMessageBox>
#include <OtoUtil/otofilereader.h>

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

QVector<OtoEntryList> OtoFileMultipleLoadWidget::entryLists() const
{
    QVector<OtoEntryList> result;

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

void OtoFileMultipleLoadWidget::loadFiles(const QStringList& fileNames)
{
    for (const auto &fileName : fileNames){
        if (!QFileInfo::exists(fileName)){
            QMessageBox::critical(this, tr("File not exists"), tr("The file \"%1\" not exists. Please check and try again.").arg(fileName));
            continue;
        }

        if (this->fileNames().contains(fileName))
        {
            QMessageBox::warning(this, tr("Has been readed"), tr("\"%1\" oto entries has been loaded.").arg(fileName));
            continue;
        }

        OtoFileReader reader(fileName);
        auto entryList = reader.getEntryList();

        if (entryList.isEmpty())
        {
            QMessageBox::critical(this, {}, tr("The given file \"%1\" is empty, or contains invalid data only.").arg(fileName));
            continue;
        }

        model->addData(fileName, entryList);
    }
    constexpr auto COLUMN_OTO_FILENAME = 0;
    ui->otoFileTableView->resizeColumnToContents(COLUMN_OTO_FILENAME);
}

void OtoFileMultipleLoadWidget::disableModify()
{
    ui->openFileNameEdit->hide();
    ui->loadButton->hide();
    ui->removeButton->hide();
    ui->line->hide();
    ui->line_2->hide();
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

    loadFiles(fileNames);

    ui->openFileNameEdit->setFileName("");
    refreshButtonEnableState();
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
    ui->showContentButton->setEnabled(count() > 0 && currentRow() >= 0);
}

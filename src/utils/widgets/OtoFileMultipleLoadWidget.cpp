#include "OtoFileMultipleLoadWidget.h"
#include "ui_OtoFileMultipleLoadWidget.h"

#include <QMessageBox>

#include "../dialogs/showotolistdialog.h"
#include "otoUtils/OtoFileReader.h"
#include "utils/misc/Misc.h"

OtoFileMultipleLoadWidget::OtoFileMultipleLoadWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::OtoFileMultipleLoadWidget)
{
    ui->setupUi(this);
    ui->otoFileTableView->setModel(model);
    connect(model, qOverload<>(&OtoFileListModel::dataChanged), this, &OtoFileMultipleLoadWidget::dataChanged);
    connect(ui->loadButton, &QPushButton::clicked, this, &OtoFileMultipleLoadWidget::appendOtoFile);
    connect(ui->removeButton, &QPushButton::clicked, this, &OtoFileMultipleLoadWidget::removeOtoFile);
    connect(ui->showContentButton, &QPushButton::clicked, this, &OtoFileMultipleLoadWidget::showOtoList);
    connect(ui->otoFileTableView->selectionModel(), &QItemSelectionModel::selectionChanged, this,
            &OtoFileMultipleLoadWidget::onSelectionChanged);

    ui->openFileNameEdit->setMultipleMode(true);

    refreshButtonEnableState();
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
    // As we have a (total) item at the end
    return model->rowCount() - 1;
}

QVector<OtoEntryList> OtoFileMultipleLoadWidget::entryLists() const
{
    QVector<OtoEntryList> result;

    auto datas = model->datas();
    for (const auto &data : datas) {
        result.append(data.entryList);
    }

    return result;
}

QStringList OtoFileMultipleLoadWidget::fileNames() const
{
    QStringList result;

    auto datas = model->datas();
    for (const auto &data : datas) {
        result.append(data.fileName);
    }

    return result;
}

void OtoFileMultipleLoadWidget::loadFiles(const QStringList &fileNames)
{
    for (const auto &fileName : fileNames) {
        if (!QFileInfo::exists(fileName)) {
            QMessageBox::critical(this, tr("File not exists"),
                                  tr("The file \"%1\" not exists. Please check and try again.").arg(fileName));
            continue;
        }

        if (this->fileNames().contains(fileName)) {
            QMessageBox::warning(this, tr("Has been readed"), tr("\"%1\" oto entries has been loaded.").arg(fileName));
            continue;
        }

        auto codec = Misc::detectCodecAndAskUserIfNotShiftJIS(fileName, parentWidget());
        OtoFileReader reader(fileName);
        reader.setTextCodec(codec);

        auto entryList = reader.read();

        const auto &errors = reader.readErrors();
        if (!errors.isEmpty()) {
            QStringList errorLines;
            constexpr int maxDisplay = 20;
            for (int i = 0; i < errors.size() && i < maxDisplay; i++) {
                const auto &e = errors[i];
                auto content = e.content.left(60);
                if (e.content.size() > 60)
                    content += QStringLiteral("…");
                errorLines.append(tr("Line %1: %2 — %3")
                                      .arg(e.lineNumber)
                                      .arg(content)
                                      .arg(OtoEntry::errorString(e.error)));
            }
            auto msg = tr("The following lines in \"%1\" could not be parsed and were skipped:").arg(fileName)
                       + "\n\n" + errorLines.join("\n");
            if (errors.size() > maxDisplay)
                msg += "\n" + tr("…and %1 more.").arg(errors.size() - maxDisplay);
            msg += "\n\n" + tr("These lines will be lost if you save the file.");
            QMessageBox::warning(this, {}, msg);
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
    connect(dialog, &QObject::destroyed, [currentList]() { delete currentList; });
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
    if (model->rowCount() > 0) {
        QSet<int> selectedRowsSet;
        auto selectedIndexes = ui->otoFileTableView->selectionModel()->selection().indexes();
        for (auto index : qAsConst(selectedIndexes)) {
            selectedRowsSet.insert(index.row());
        }
        auto selectedRows = selectedRowsSet.values();
        std::sort(selectedRows.begin(), selectedRows.end(), std::greater<>());

        for (auto i : selectedRows) {
            model->deleteData(i);
        }
    }
}

void OtoFileMultipleLoadWidget::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected)
    refreshButtonEnableState();
    // Prevent showing multiple list
    ui->showContentButton->setEnabled(ui->showContentButton->isEnabled() && selected.count() <= 1);
}

int OtoFileMultipleLoadWidget::currentRow()
{
    return ui->otoFileTableView->currentIndex().row();
}

void OtoFileMultipleLoadWidget::refreshButtonEnableState()
{
    ui->removeButton->setEnabled(count() > 0 && currentRow() < count());
    ui->showContentButton->setEnabled(count() > 0 && currentRow() >= 0 && currentRow() < count());
}

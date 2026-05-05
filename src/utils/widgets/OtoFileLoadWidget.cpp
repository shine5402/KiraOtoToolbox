#include "OtoFileLoadWidget.h"
#include "ui_OtoFileLoadWidget.h"

#include <QMessageBox>

#include "../dialogs/ShowOtoListDialog.h"
#include "otoUtils/OtoFileReader.h"
#include "utils/misc/Misc.h"

OtoFileLoadWidget::OtoFileLoadWidget(QWidget *parent) : QWidget(parent), ui(new Ui::OtoFileLoadWidget)
{
    ui->setupUi(this);
    connect(ui->loadButton, &QPushButton::clicked, this, &OtoFileLoadWidget::loadOtoFile);
    connect(ui->showOtoListButton, &QPushButton::clicked, this, &OtoFileLoadWidget::showOtoListDialog);
}

OtoFileLoadWidget::~OtoFileLoadWidget()
{
    delete ui;
}

void OtoFileLoadWidget::setFileName(const QString &fileName)
{
    ui->openFileNameEdit->setFileName(fileName);
}

QString OtoFileLoadWidget::fileName() const
{
    return ui->openFileNameEdit->fileName();
}

OtoEntryList OtoFileLoadWidget::getEntryList() const
{
    return entryList;
}

bool OtoFileLoadWidget::isEntryListReaded() const
{
    return entryListReaded;
}

void OtoFileLoadWidget::reset()
{
    setFileName("");
    entryList.clear();
    entryListReaded = false;

    ui->showOtoListButton->setEnabled(false);
    ui->countLabel->setText(tr("Oto data has not been loaded"));
    ui->loadOtoWidget->setEnabled(true);
    emit resetted();
}

void OtoFileLoadWidget::load()
{
    loadOtoFile();
}

void OtoFileLoadWidget::pretendLoaded(const QString &fileName, const OtoEntryList &entryList)
{
    ui->openFileNameEdit->setFileName(fileName);
    this->entryList = entryList;
    entryListReaded = true;
    setUpLoadedUI();
}

void OtoFileLoadWidget::setUpLoadedUI()
{
    ui->showOtoListButton->setEnabled(true);

    ui->countLabel->setText(tr("%1 oto entries has been loaded.").arg(entryList.count()));
    ui->loadOtoWidget->setDisabled(true);
}

void OtoFileLoadWidget::loadOtoFile()
{
    auto path = ui->openFileNameEdit->fileName();

    if (!QFileInfo::exists(path)) {
        QMessageBox::critical(this, tr("File not exists"),
                              tr("The file \"%1\" not exists. Please check and try again.").arg(path));
        return;
    }

    auto codec = Misc::detectCodecAndAskUserIfNotShiftJIS(path, parentWidget());
    OtoFileReader reader(path);
    reader.setTextCodec(codec);
    entryList = reader.read();

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
        auto msg = tr("The following lines in \"%1\" could not be parsed and were skipped:").arg(path)
                   + "\n\n" + errorLines.join("\n");
        if (errors.size() > maxDisplay)
            msg += "\n" + tr("…and %1 more.").arg(errors.size() - maxDisplay);
        msg += "\n\n" + tr("These lines will be lost if you save the file.");
        QMessageBox::warning(this, {}, msg);
    }

    entryListReaded = true;
    setUpLoadedUI();

    emit loaded();
}

void OtoFileLoadWidget::showOtoListDialog()
{
    auto dialog = new ShowOtoListDialog(&entryList, this);
    dialog->open();
}

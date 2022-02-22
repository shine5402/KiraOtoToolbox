#include "otofileloadwidget.h"
#include "ui_otofileloadwidget.h"

#include <QMessageBox>
#include <OtoUtil/otofilereader.h>
#include "../dialogs/showotolistdialog.h"
#include <utils/misc/misc.h>

OtoFileLoadWidget::OtoFileLoadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OtoFileLoadWidget)
{
    ui->setupUi(this);
    connect(ui->loadButton, &QPushButton::clicked, this, &OtoFileLoadWidget::loadOtoFile);
    connect(ui->showOtoListButton, &QPushButton::clicked, this, &OtoFileLoadWidget::showOtoListDialog);
}

OtoFileLoadWidget::~OtoFileLoadWidget()
{
    delete ui;
}

void OtoFileLoadWidget::setFileName(const QString& fileName)
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

void OtoFileLoadWidget::pretendLoaded(const QString& fileName, const OtoEntryList& entryList)
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

    if (!QFileInfo::exists(path)){
        QMessageBox::critical(this, tr("File not exists"),
                              tr("The file \"%1\" not exists. Please check and try again.").arg(path));
        return;
    }

    auto codec = Misc::detectCodecAndAskUserIfNotShiftJIS(path, parentWidget());
    OtoFileReader reader(path);
    reader.setTextCodec(codec);
    entryList = reader.getEntryList();
    if (entryList.isEmpty())
    {
        QMessageBox::critical(this, {},
                              tr("The given file \"%1\" is empty, or contains invalid data only.").arg(path));
        return;
    }
    entryListReaded = true;
    setUpLoadedUI();

    emit loaded();
}

void OtoFileLoadWidget::showOtoListDialog()
{
    auto dialog = new ShowOtoListDialog(&entryList ,this);
    dialog->open();
}

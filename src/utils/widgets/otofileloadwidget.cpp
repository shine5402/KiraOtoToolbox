#include "otofileloadwidget.h"
#include "ui_otofileloadwidget.h"

#include <QMessageBox>
#include <OtoUtil/otofilereader.h>
#include "../dialogs/showotolistdialog.h"

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

void OtoFileLoadWidget::loadOtoFile()
{
    auto path = ui->openFileNameEdit->fileName();

    if (!QFileInfo::exists(path)){
        QMessageBox::critical(this, tr("File not exists"), tr("The file \"%1\" not exists. Please check and try again."));
        return;
    }

    OtoFileReader reader(path);
    entryList = reader.getEntryList();
    entryListReaded = true;

    ui->showOtoListButton->setEnabled(true);

    ui->countLabel->setText(tr("%1 oto entries has been loaded.").arg(entryList.count()));
    ui->loadOtoWidget->setDisabled(true);

    emit loaded();
}

void OtoFileLoadWidget::showOtoListDialog()
{
    auto dialog = new ShowOtoListDialog(&entryList ,this);
    dialog->open();
}

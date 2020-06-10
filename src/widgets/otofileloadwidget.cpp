#include "otofileloadwidget.h"
#include "ui_otofileloadwidget.h"

#include <QMessageBox>
#include <otofilereader.h>
#include "showotolistdialog.h"

OtoFileLoadWidget::OtoFileLoadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OtoFileLoadWidget)
{
    ui->setupUi(this);
}

OtoFileLoadWidget::~OtoFileLoadWidget()
{
    delete ui;
}

void OtoFileLoadWidget::loadOtoFile()
{
    auto path = ui->openFileNameEdit->getFileName();

    if (!QFileInfo::exists(path)){
#ifdef SHINE5402OTOBOX_TEST
        Q_ASSERT(false);
#endif
        QMessageBox::critical(this, tr("文件不存在"), tr("您指定的文件不存在，请检查后再试。"));\
        return;
    }

    OtoFileReader reader(path);
    entryList = reader.getEntryList();
    entryList_readed = true;

    //ui->optionGroupBox->setEnabled(true);
    //ui->saveOptionGroupBox->setEnabled(true);
    ui->showOtoListButton->setEnabled(true);

    ui->countLabel->setText(tr("加载了 %1 条原音设定。").arg(entryList.count()));
    ui->loadOtoWidget->setDisabled(true);

    emit loaded();
}

void OtoFileLoadWidget::showOtoListDialog()
{
    auto dialog = new ShowOtoListDialog(&entryList ,this);
    dialog->open();
}

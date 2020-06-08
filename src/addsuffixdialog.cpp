#include "addsuffixdialog.h"
#include "ui_addsuffixdialog.h"
#include <QFileDialog>
#include <otofilereader.h>
#include "showotolistdialog.h"
#include <QMessageBox>

AddSuffixDialog::AddSuffixDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSuffixDialog)
{
    ui->setupUi(this);
    connect(ui->browseButton_open, &QPushButton::clicked, this, &AddSuffixDialog::openFilePathBrowse);
    connect(ui->loadButton, &QPushButton::clicked, this, &AddSuffixDialog::loadOtoFile);
    connect(ui->showOtoListButton, &QPushButton::clicked, this, &AddSuffixDialog::showOtoListDialog);
    connect(ui->browseButton_save, &QPushButton::clicked, this, &AddSuffixDialog::saveFilePathBrowse);

}

AddSuffixDialog::~AddSuffixDialog()
{
    delete ui;
}

void AddSuffixDialog::accept()
{
    auto entryListWorking = entryList;
    for (auto& i : entryListWorking)
    {
        i.setAlias(ui->prefixLineEdit->text() + i.alias() + ui->suffixLineEdit->text());
    }
    auto dialog = new ShowOtoListDialog(&entryListWorking, this);
    dialog->setWindowTitle(tr("确认更改"));
    dialog->setLabel(tr("以下显示了添加前后缀后的原音设定数据。点击“确定”来确认此修改，点击“取消”以取消本次操作。"));
    auto code = dialog->exec();
    if (code == QDialog::Rejected)
        return;

    QFile file(ui->saveToPathRadioButton->isChecked()? ui->fileNameEdit_save->text() : ui->fileNameEdit_open->text());
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
        auto code = OtoEntryFunctions::writeOtoListToFile(file, entryListWorking);
        if (code == -1)
        {
#ifdef SHINE5402OTOBOX_TEST
            Q_ASSERT(false);
#endif
            QMessageBox::critical(this, tr("保存失败"), tr("无法保存文件。"));
        }
        else
        {
#ifndef SHINE5402OTOBOX_TEST
            QMessageBox::information(this, tr("成功"), tr("文件已经保存好了。"));
#endif

        }
    }
    else{
#ifdef SHINE5402OTOBOX_TEST
        Q_ASSERT(false);
#endif
        QMessageBox::critical(this, tr("无法打开指定路径"), tr("无法打开 %1。").arg(file.fileName()));
    }
    QDialog::accept();
}

void AddSuffixDialog::openFilePathBrowse()
{
    auto path = QFileDialog::getOpenFileName(this,tr("选择一个原音设定文件"),{},tr("原音设定文件 (*.ini);;所有文件 (*.*)"));
    if (!path.isEmpty())
        ui->fileNameEdit_open->setText(path);
}

void AddSuffixDialog::loadOtoFile()
{
    auto path = ui->fileNameEdit_open->text();

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

    ui->optionGroupBox->setEnabled(true);
    ui->saveOptionGroupBox->setEnabled(true);
    ui->showOtoListButton->setEnabled(true);

    ui->countLabel->setText(tr("加载了 %1 条原音设定。").arg(entryList.count()));
    ui->loadOtoWidget->setDisabled(true);
}

void AddSuffixDialog::showOtoListDialog()
{
    auto dialog = new ShowOtoListDialog(&entryList ,this);
    dialog->open();
}

void AddSuffixDialog::saveFilePathBrowse()
{
    auto path = QFileDialog::getSaveFileName(this, tr("指定保存路径"), {}, tr("原音设定文件 (*.ini);;所有文件 (*.*)"));
    if (!path.isEmpty())
        ui->fileNameEdit_save->setText(path);
}

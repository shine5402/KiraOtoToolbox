#include "filenameeditwithbrowse.h"
#include "ui_filenameeditwithbrowse.h"
#include <QFileDialog>

FileNameEditWithBrowse::FileNameEditWithBrowse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileNameEditWithBrowse)
{
    ui->setupUi(this);

    connect(ui->browseButton, &QPushButton::clicked, this, &FileNameEditWithBrowse::browse);
}

FileNameEditWithBrowse::~FileNameEditWithBrowse()
{
    delete ui;
}

QString FileNameEditWithBrowse::getFileName() const
{
    auto fileName = ui->fileNameEdit->text();
    const bool isSurroundByDoubleQuotes = fileName.startsWith("\"") && fileName.endsWith("\"");
    const bool isSurroundBySingleQuotes = fileName.startsWith("'") && fileName.endsWith("'");
    if (isSurroundByDoubleQuotes || isSurroundBySingleQuotes)
        fileName = fileName.mid(1, fileName.count() - 2);
    return fileName;
}

void FileNameEditWithBrowse::setFileName(const QString& value)
{
    ui->fileNameEdit->setText(value);
}

FileNameEditWithBrowse::Purpose FileNameEditWithBrowse::getPurpose() const
{
    return purpose;
}

void FileNameEditWithBrowse::setPurpose(const Purpose& value)
{
    purpose = value;
}

void FileNameEditWithBrowse::openFilePathBrowse()
{
    //TODO: 把这里的参数拆出来
    auto path = QFileDialog::getOpenFileName(this,tr("选择一个原音设定文件"),{},tr("原音设定文件 (*.ini);;所有文件 (*.*)"));
    if (!path.isEmpty())
        ui->fileNameEdit->setText(path);
}

void FileNameEditWithBrowse::saveFilePathBrowse()
{
    auto path = QFileDialog::getSaveFileName(this, tr("指定保存路径"), {}, tr("原音设定文件 (*.ini);;所有文件 (*.*)"));
    if (!path.isEmpty())
        ui->fileNameEdit->setText(path);
}

void FileNameEditWithBrowse::browse()
{
    switch (purpose) {
        case Open: openFilePathBrowse();break;
        case Save: saveFilePathBrowse();break;
    }
}

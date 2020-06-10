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
    //auto path = QFileDialog::getOpenFileName(this,tr("选择一个原音设定文件"),{},tr("原音设定文件 (*.ini);;所有文件 (*.*)"));
    auto path = QFileDialog::getOpenFileName(this,caption,dir,filter,selectedFilter,options);
    if (!path.isEmpty())
        ui->fileNameEdit->setText(path);
}

void FileNameEditWithBrowse::saveFilePathBrowse()
{
    //auto path = QFileDialog::getSaveFileName(this, tr("指定保存路径"), {}, tr("原音设定文件 (*.ini);;所有文件 (*.*)"));
    auto path = QFileDialog::getSaveFileName(this, caption, dir, filter, selectedFilter, options);
    if (!path.isEmpty())
        ui->fileNameEdit->setText(path);
}

QString* FileNameEditWithBrowse::getSelectedFilter() const
{
    return selectedFilter;
}

void FileNameEditWithBrowse::setSelectedFilter(QString* value)
{
    selectedFilter = value;
}

QFileDialog::Options FileNameEditWithBrowse::getOptions() const
{
    return options;
}

void FileNameEditWithBrowse::setOptions(const QFileDialog::Options& value)
{
    options = value;
}

void FileNameEditWithBrowse::setParameters(const QString& caption, const QString& dir, const QString& filter, QString* selectedFilter, QFileDialog::Options options)
{
    setCaption(caption);
    setDir(dir);
    setFilter(filter);
    setSelectedFilter(selectedFilter);
    setOptions(options);
}

QString FileNameEditWithBrowse::getFilter() const
{
    return filter;
}

void FileNameEditWithBrowse::setFilter(const QString& value)
{
    filter = value;
}

QString FileNameEditWithBrowse::getDir() const
{
    return dir;
}

void FileNameEditWithBrowse::setDir(const QString& value)
{
    dir = value;
}

QString FileNameEditWithBrowse::getCaption() const
{
    return caption;
}

void FileNameEditWithBrowse::setCaption(const QString& value)
{
    caption = value;
}

void FileNameEditWithBrowse::browse()
{
    switch (purpose) {
        case Open: openFilePathBrowse();break;
        case Save: saveFilePathBrowse();break;
    }
}

FileNameEditWithOpenBrowse::FileNameEditWithOpenBrowse(QWidget* parent) : FileNameEditWithBrowse(parent)
{
    setPurpose(Open);
}

FileNameEditWithSaveBrowse::FileNameEditWithSaveBrowse(QWidget* parent) : FileNameEditWithBrowse(parent)
{
    setPurpose(Save);
}

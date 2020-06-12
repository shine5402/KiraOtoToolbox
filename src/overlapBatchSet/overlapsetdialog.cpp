#include "overlapsetdialog.h"
#include "ui_overlapsetdialog.h"
#include <QFileDialog>
#include <otofilereader.h>
#include <QMessageBox>
#include "utils/dialogs/showotolistdialog.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QInputDialog>
#include "utils/models/otolistoverlapshowchangemodel.h"
#include "utils/dialogs/showotolistdialog.h"

OverlapSetDialog::OverlapSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OverlapSetDialog)
{
    ui->setupUi(this);

    connect(ui->browseButton_open, &QPushButton::clicked, this, &OverlapSetDialog::openFilePathBrowse);
    connect(ui->loadButton, &QPushButton::clicked, this, &OverlapSetDialog::loadOtoFile);
    connect(ui->showOtoListButton, &QPushButton::clicked, this, &OverlapSetDialog::showOtoListDialog);
    connect(ui->setStartWithPresetComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OverlapSetDialog::switchPreset);
    connect(ui->setStartWithLoadFromFileRadioButton, &QRadioButton::toggled, this, &OverlapSetDialog::clearWorkingStartList);
    connect(ui->setStartWithPresetRadioButton, &QRadioButton::toggled, this, &OverlapSetDialog::switchToUsePreset);
    connect(ui->setStartWithInputButton, &QPushButton::clicked, this, &OverlapSetDialog::getStartListFromUserInput);
    connect(ui->browseButton_save, &QPushButton::clicked, this, &OverlapSetDialog::saveFilePathBrowse);

    loadPreset();
    if (!presetList.isEmpty()){
        ui->setStartWithPresetComboBox->addItems([&]() -> QStringList{
                                                     QStringList items;
                                                     for (auto i : presetList)
                                                     {
                                                         items.append(i.name);
                                                     }
                                                     return items;
                                                 }());
        ui->setStartWithPresetComboBox->setCurrentIndex(0);
    }
    else
    {
        ui->setStartWithPresetComboBox->addItem(tr("（无）"));
        ui->setStartWithPresetComboBox->setEnabled(false);
        ui->setStartWithPresetRadioButton->setEnabled(false);
        ui->setStartWithLoadFromFileRadioButton->setChecked(true);
    }
    startListModel.setStringList(*workingStartList);
    ui->setStartWithListView->setModel(&startListModel);
}

const QStringList OverlapSetDialog::emptyStringList{};

OverlapSetDialog::~OverlapSetDialog()
{
    delete ui;
}

void OverlapSetDialog::loadPreset()
{
    QFile file(":/overlap_start_preset/preset_list.json");
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        auto data = file.readAll();
        QJsonParseError error;
        auto jsonDoc = QJsonDocument::fromJson(data, &error);
        if (!jsonDoc.isNull())
        {
            if (jsonDoc.isArray())
            {
                auto array = jsonDoc.array();
                for (auto value : array)
                {
                    auto obj = value.toObject();
                    auto name = obj.value("name").toString();
                    auto path = obj.value("path").toString();
                    if (name.isEmpty() || path.isEmpty())
                    {
#ifdef SHINE5402OTOBOX_TEST
                        Q_ASSERT(false);
#endif
                        QMessageBox::warning(this,tr("有预设读取失败"),tr("预设描述值至少有一项为空。出现问题的预设将无法使用。"));
                        continue;
                    }
                    QFile file(path);
                    if (file.open(QFile::ReadOnly | QFile::Text))
                    {
                        auto data = file.readAll();
                        if (data.isEmpty())
                        {
#ifdef SHINE5402OTOBOX_TEST
                            Q_ASSERT(false);
#endif
                            QMessageBox::warning(this,tr("有预设读取失败"),tr("预设值为空。出现问题的预设将无法使用。"));
                        }
                        presetList.append({name, QString::fromUtf8(data).split("\n",QString::SplitBehavior::SkipEmptyParts)});
                    }
                    else
                    {
#ifdef SHINE5402OTOBOX_TEST
                        Q_ASSERT(false);
#endif
                        QMessageBox::warning(this,tr("有预设读取失败"),tr("读取预设"));
                    }
                    //presetList.append({obj.value("name")})
                }
            }
            else
            {
#ifdef SHINE5402OTOBOX_TEST
                Q_ASSERT(false);
#endif
                QMessageBox::warning(this, tr("预设清单读取失败"),tr("解析预设清单时出现错误：根元素不是Array。预设将不可用。"));
            }
        }
        else
        {
#ifdef SHINE5402OTOBOX_TEST
            Q_ASSERT(false);
#endif
            QMessageBox::warning(this, tr("预设清单读取失败"),tr("解析预设清单时出现错误，错误说明为 %1。预设将不可用。").arg(error.errorString()));
        }
    }
    else
    {
#ifdef SHINE5402OTOBOX_TEST
        Q_ASSERT(false);
#endif
        QMessageBox::warning(this, tr("预设清单读取失败"),tr("程序无法打开预设清单文件，预设将不可用。"));
    }
}

void OverlapSetDialog::setWorkingStartList(const QStringList* list)
{
    workingStartList = list;
    startListModel.setStringList(*workingStartList);
}

void OverlapSetDialog::accept()
{
    auto entryListWorking = entryList;
    QVector<int> matched;
    //匹配开头并设置为指定数值
    if (ui->setStartWithCheckBox->isChecked())
    {
        for (int i = 0; i < entryListWorking.count(); ++i)
        {
            auto entry = entryListWorking.at(i);
            for (auto s : *workingStartList)
            {
                if (entry.alias().startsWith(s) || (ui->matchStartOtoCheckBox->isChecked() && entry.alias().startsWith("- " + s)))
                {
                    entry.setOverlap(ui->setStartWithSpinBox->value());
                    entryListWorking.replace(i, entry);
                    matched.append(i);
                    break;
                }
            }
        }
    }
    //设置三分之一
    if (ui->OneThirdCheckBox->isChecked())
    {
        for (int i = 0; i < entryListWorking.count(); ++i)
        {
            if (!matched.contains(i))
            {
                auto entry = entryListWorking.at(i);
                entry.setOverlap(entry.preUtterance() / 3);
                entryListWorking.replace(i, entry);
            }
        }
    }

    //显示差异和向用户确认
    QVector<double> newOverlapList;
    for (auto i : entryListWorking)
    {
        newOverlapList.append(i.overlap());
    }
    auto model = new OtoListOverlapShowChangeModel(&entryList, &newOverlapList, this);
    auto dialog = new ShowOtoListDialog(model, this);
    dialog->setWindowTitle(tr("确认对Overlap的更改"));
    dialog->setLabel(tr("以下显示了根据您的要求要对原音设定数据执行的修改。点击“确定”来确认此修改，点击“取消”以取消本次操作。"));
    auto code = dialog->exec();
    if (code == QDialog::Rejected)
        return;

    //写入文件
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

void OverlapSetDialog::openFilePathBrowse()
{
    auto path = QFileDialog::getOpenFileName(this,tr("选择一个原音设定文件"),{},tr("原音设定文件 (*.ini);;所有文件 (*.*)"));
    if (!path.isEmpty())
        ui->fileNameEdit_open->setText(path);
}

void OverlapSetDialog::loadOtoFile()
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

void OverlapSetDialog::showOtoListDialog()
{
    auto dialog = new ShowOtoListDialog(&entryList ,this);
    dialog->open();
}

void OverlapSetDialog::switchPreset(int index)
{
    setWorkingStartList(&presetList.at(index).content);
}

void OverlapSetDialog::clearWorkingStartList()
{
    setWorkingStartList(&emptyStringList);
}

void OverlapSetDialog::loadStartListFromFile()
{
    auto path = QFileDialog::getOpenFileName(this, tr("选择文件"),{},tr("文本文件 (*.txt);;所有文件 (*.*)"));
    if (!path.isEmpty())
    {
        QFile file(path);
        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            auto data = file.readAll();
            notPresetStartList = QString::fromUtf8(data).split("\n",QString::SkipEmptyParts);
            setWorkingStartList(&notPresetStartList);
            ui->setStartWithListView->setEnabled(true);
        }
        else {
#ifdef SHINE5402OTOBOX_TEST
            Q_ASSERT(false);
#endif
            QMessageBox::critical(this,tr("读取失败"),tr("无法打开指定的文件。"));

        }
    }
}

void OverlapSetDialog::switchToUsePreset()
{
    switchPreset(ui->setStartWithPresetComboBox->currentIndex());
}

void OverlapSetDialog::getStartListFromUserInput()
{
    bool ok = false;
    auto result = QInputDialog::getMultiLineText(this, tr("输入开头列表"),tr("请输入要被匹配的开头字符串的列表，一行一个。"),workingStartList->join("\n"),&ok);
    if (ok)
    {
        notPresetStartList = result.split("\n",QString::SkipEmptyParts);
        setWorkingStartList(&notPresetStartList);
    }
}

void OverlapSetDialog::saveFilePathBrowse()
{
    auto path = QFileDialog::getSaveFileName(this, tr("指定保存路径"), {}, tr("原音设定文件 (*.ini);;所有文件 (*.*)"));
    if (!path.isEmpty())
        ui->fileNameEdit_save->setText(path);
}

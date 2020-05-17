#include "removeduplicatedialog.h"
#include "ui_removeduplicatedialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include "otofilereader.h"
#include "showotolistdialog.h"
#include <QInputDialog>
#include "otolistaliasshowchangemodel.h"
#include <algorithm>
#ifdef SHINE5402OTOBOX_TEST
#include <QTimer>
#endif


RemoveDuplicateDialog::RemoveDuplicateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveDuplicateDialog)
{
    ui->setupUi(this);

    connect(ui->browseButton_open, &QPushButton::clicked, this, &RemoveDuplicateDialog::openFilePathBrowse);
    connect(ui->loadButton, &QPushButton::clicked, this, &RemoveDuplicateDialog::loadOtoFile);
    connect(ui->showOtoListButton, &QPushButton::clicked, this, &RemoveDuplicateDialog::showOtoListDialog);
    connect(ui->addSuffixButton, &QPushButton::clicked, this, &RemoveDuplicateDialog::addSuffix);
    connect(ui->deleteSuffixButton, &QPushButton::clicked, this, &RemoveDuplicateDialog::deleteSuffix);
    connect(ui->modifySuffixButton, &QPushButton::clicked, this, &RemoveDuplicateDialog::modifySuffix);
    connect(ui->browseButton_save, &QPushButton::clicked, this, &RemoveDuplicateDialog::saveFilePathBrowse);
    connect(ui->browseButton_save_deleted, &QPushButton::clicked, this, &RemoveDuplicateDialog::saveDeletedFilePathBrowse);
}

RemoveDuplicateDialog::~RemoveDuplicateDialog()
{
    delete ui;
}

void RemoveDuplicateDialog::openFilePathBrowse()
{
    auto path = QFileDialog::getOpenFileName(this,tr("选择一个原音设定文件"),{},tr("原音设定文件 (*.ini);;所有文件 (*.*)"));
    if (!path.isEmpty())
        ui->fileNameEdit_open->setText(path);
}

void RemoveDuplicateDialog::loadOtoFile()
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

void RemoveDuplicateDialog::showOtoListDialog()
{
    auto dialog = new ShowOtoListDialog(&entryList ,this);
    dialog->open();
}


void RemoveDuplicateDialog::addSuffix()
{

    bool ok;
#ifdef SHINE5402OTOBOX_TEST
        auto suffix = QString("TestAdd");
        ok = true;
#endif
        #ifndef SHINE5402OTOBOX_TEST
    auto suffix = QInputDialog::getText(this, tr("输入新后缀"), tr("输入要添加到后缀列表的新后缀"), QLineEdit::Normal, {}, &ok);
    #endif
    if (ok)
    {
        if (suffix.isEmpty())
        {
#ifdef SHINE5402OTOBOX_TEST
        Q_ASSERT(false);
#endif
            QMessageBox::critical(this, tr("输入值为空"),tr("提供的输入是空的。后缀列表不会做出更改。"));
            return;
        }
        ui->suffixListWidget->addItem(suffix);
    }
}

void RemoveDuplicateDialog::deleteSuffix()
{

    auto selectedItems = ui->suffixListWidget->selectedItems();
    if (selectedItems.count() == 0)
    {
#ifdef SHINE5402OTOBOX_TEST
        Q_ASSERT(false);
#endif
        QMessageBox::warning(this, tr("没有选择"), tr("没有后缀项被选中，因而无法删除。"));
        return;
    }
    auto item = selectedItems.at(0);
#ifndef SHINE5402OTOBOX_TEST


    auto shouldDelete = QMessageBox::question(this, tr("确认删除"), tr("真的要删除 %1 吗？").arg(item->text()));
    if (shouldDelete == QMessageBox::Yes)
    {
#endif
        ui->suffixListWidget->removeItemWidget(item);
        delete item;
#ifndef SHINE5402OTOBOX_TEST
    }
#endif
}

void RemoveDuplicateDialog::modifySuffix()
{
    auto selectedItems = ui->suffixListWidget->selectedItems();
    if (selectedItems.count() == 0)
    {
#ifdef SHINE5402OTOBOX_TEST
        Q_ASSERT(false);
#endif
        QMessageBox::warning(this, tr("没有选择"), tr("没有后缀项被选中，因而无法修改。"));
        return;
    }
    auto item = selectedItems.at(0);
#ifndef SHINE5402OTOBOX_TEST
    bool ok;
    auto modified = QInputDialog::getText(this, tr("输入新后缀"), tr("指定一个新后缀用来替换 %1").arg(item->text()), QLineEdit::Normal, item->text(), &ok);
    if (ok)
    {
#endif
#ifdef SHINE5402OTOBOX_TEST
        auto modified = QString("TestModify");
#endif
        item->setText(modified);
            #ifndef SHINE5402OTOBOX_TEST
    }
#endif
}



void RemoveDuplicateDialog::saveFilePathBrowse()
{
    auto path = QFileDialog::getSaveFileName(this, tr("指定保存路径"), {}, tr("原音设定文件 (*.ini);;所有文件 (*.*)"));
    if (!path.isEmpty())
        ui->fileNameEdit_save->setText(path);
}

void RemoveDuplicateDialog::saveDeletedFilePathBrowse()
{
    auto path = QFileDialog::getSaveFileName(this, tr("指定保存路径"), {}, tr("原音设定文件 (*.ini);;所有文件 (*.*)"));
    if (!path.isEmpty())
        ui->fileNameEdit_save_deleted->setText(path);
}

void RemoveDuplicateDialog::RemoveDuplicateDialog::accept()
{
    QStringList compareStringList;
    auto entryListWorking = entryList;

    for (int i = 0; i < entryList.count(); ++i)
    {
        compareStringList.append(entryList.at(i).alias());
    }

    //处理特定后缀
    auto isIgnoreSpecificSuffix = ui->ignoreSpecificSuffixCheckBox->isChecked();
    QHash<int, QString> removedSpecificSuffixMap; //为整理时添加回特定后缀留存
    if (isIgnoreSpecificSuffix)
        for (int i = 0; i < entryList.count(); ++i)
        {
            for (int itemID = 0; itemID < ui->suffixListWidget->count(); ++itemID)
            {
                auto currentItem = ui->suffixListWidget->item(itemID);
                if (compareStringList.at(i).endsWith(currentItem->text()))
                {
                    auto result = OtoEntryFunctions::removeSuffix(compareStringList.at(i), currentItem->text());
                    compareStringList.replace(i, result);
                    removedSpecificSuffixMap.insert(i, currentItem->text());
                }
            }
        }

    //处理音高后缀
    auto isIgnorePitchSuffix = ui->ignorePitchSuffixCheckBox->isChecked();
    QHash<int, QString> removedPitchStringList; //为整理时添加回音高后缀留存
    if (isIgnorePitchSuffix)
        for (int i = 0; i < entryList.count(); ++i)
        {
            auto bottomPitch = QString("%1%2").arg(ui->bottomPitchComboBox->currentText()).arg(ui->bottomPitchSpinBox->value());
            auto topPitch = QString("%1%2").arg(ui->topPitchComboBox->currentText()).arg(ui->topPitchSpinBox->value());
            QString removedPitch {};
            auto result = OtoEntryFunctions::removePitchSuffix(compareStringList.at(i), bottomPitch, topPitch,
                                                               ui->caseSensitiveCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive,
                                                               ui->caseComboBox->currentIndex() == 0 ? OtoEntryFunctions::Upper : OtoEntryFunctions::Lower, &removedPitch);
            compareStringList.replace(i, result);
            if (!removedPitch.isEmpty())
                removedPitchStringList.insert(i, removedPitch);
        }

    //处理数字后缀（重复）
    QStringList digitSuffixList;
    for (int i = 0; i < entryList.count(); ++i)
    {
        auto suffix = OtoEntryFunctions::getDigitSuffix(compareStringList.at(i));
        digitSuffixList.append(suffix);
        compareStringList.replace(i, OtoEntryFunctions::removeSuffix(compareStringList.at(i), suffix));
    }

    QMultiHash<QString, int> compareStringMap;

    for (int i = 0; i < compareStringList.count(); ++i)
    {
        compareStringMap.insertMulti(compareStringList.at(i), i);
    }

    //整理重复项

    auto shouldOrgnaize = ui->organizeCheckBox->isChecked();
    if (shouldOrgnaize){
        /*
         * 要做的事：重整重复项数字顺序，添加原后缀。
         */
        QHash <int, QString> newAlias;
        for (auto key : compareStringMap.uniqueKeys())
        {
            auto values = compareStringMap.values(key);
            std::sort(values.begin(), values.end());

            for (int i = 0; i < values.count(); ++i)
            {
                auto currentID = values.at(i);
                newAlias.insert(currentID, compareStringList.at(currentID) +
                                (i > 0 ? QString::number((ui->organizeStartFrom1CheckBox->isChecked() ? i : i + 1)) : "") +
                                (ui->organizeCaseComboBox->currentIndex() == 0 ? removedPitchStringList.value(currentID, "").toUpper() : removedPitchStringList.value(currentID, "").toLower()) +
                                removedSpecificSuffixMap.value(currentID, ""));
            }
        }
        QStringList toBeReplacedNewAlias;
        for (int i = 0; i < entryList.count(); ++i)
        {
            toBeReplacedNewAlias.append(newAlias.value(i, ""));
        }
        auto model = new OtoListAliasShowChangeModel(&entryList, &toBeReplacedNewAlias, this);
        auto askDialog = new ShowOtoListDialog(model, this);
        askDialog->setWindowTitle(tr("重复项整理结果"));
        askDialog->setLabel(tr("以下特别标出的原音设定的别名将会被重命名，其中多余的重复项将根据您的设置在下一步被删除。点击“确定”来确认此修改，点击“取消”以取消本次操作。"));
        askDialog->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

#ifdef SHINE5402OTOBOX_TEST
        QTimer::singleShot(0, askDialog, &ShowOtoListDialog::accept);
#endif
        auto shouldOrganize = askDialog->exec();
        if (shouldOrganize == QDialog::Rejected)
            return;

        for (auto currentID : newAlias.keys())
        {
            auto currentEntry = entryListWorking.at(currentID);
            currentEntry.setAlias(newAlias.value(currentID));
            entryListWorking.replace(currentID, currentEntry);
        }
    }

    //删除重复项
    auto maxAppearTime = ui->maxSpinBox->value();
    if (maxAppearTime != 0) {
        QList<int> toBeRemoved;

        for (auto key : compareStringMap.uniqueKeys())
        {
            if (compareStringMap.count(key) > maxAppearTime)
            {
                auto values = compareStringMap.values(key);
                std::sort(values.begin(), values.end());
                toBeRemoved.append(values.mid(maxAppearTime));
            }
        }
        //检查重复并确认待删除项
        OtoEntryList toBeRemovedEntryList;
        for (auto i : toBeRemoved)
        {
            toBeRemovedEntryList.append(entryListWorking.at(i));
        }
        auto askDialog = new ShowOtoListDialog(&toBeRemovedEntryList, this);
        askDialog->setWindowTitle(tr("要被删除的原音设定条目列表"));
        askDialog->setLabel(tr("以下 %1 条原音设定条目将会被删除，或是被保存到您指定的文件中。点击“确定”来确认此修改，点击“取消”以取消本次操作。").arg(toBeRemoved.count()));
        askDialog->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

#ifdef SHINE5402OTOBOX_TEST
        QTimer::singleShot(0, askDialog, &ShowOtoListDialog::accept);
#endif

        auto shouldDelete = askDialog->exec();
        if (shouldDelete == QDialog::Rejected)
            return;

        if (ui->saveDeletedCheckBox->isChecked())
        {
            QFile file(ui->fileNameEdit_save_deleted->text());
            if (file.open(QFile::WriteOnly | QFile::Text))
            {
                auto code = OtoEntryFunctions::writeOtoListToFile(file, toBeRemovedEntryList);
                if (code == -1)
                {
#ifdef SHINE5402OTOBOX_TEST
        Q_ASSERT(false);
#endif
                    auto shouldContinue = QMessageBox::critical(this, tr("被删除项保存失败"), tr("无法正常保存 %1。请问要继续操作吗？").arg(ui->fileNameEdit_save_deleted->text()), QMessageBox::Ok | QMessageBox::Cancel);
                    if (shouldContinue == QMessageBox::Cancel)
                        return;
                }
            }
            else
            {
#ifdef SHINE5402OTOBOX_TEST
        Q_ASSERT(false);
#endif
                auto shouldContinue = QMessageBox::critical(this, tr("无法打开指定路径"), tr("无法打开 %1，将不会保存被删除项到另外的文件。请问要继续操作吗？").arg(ui->fileNameEdit_save_deleted->text()), QMessageBox::Ok | QMessageBox::Cancel);
                if (shouldContinue == QMessageBox::Cancel)
                    return;
            }
        }


        for (auto i : toBeRemovedEntryList){
            entryListWorking.removeOne(i);
        }
    }




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

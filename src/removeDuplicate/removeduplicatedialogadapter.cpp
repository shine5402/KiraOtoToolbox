#include "removeduplicatedialogadapter.h"
#include "removeduplicatedialogoptionwidget.h"
#include "utils/models/otolistaliasshowchangemodel.h"
#include "utils/models/otolistshowvaluechangemodel.h"
#include "utils/dialogs/showotolistdialog.h"
#include <QMessageBox>
#ifdef SHINE5402OTOBOX_TEST
#include <QTimer>
#endif

RemoveDuplicateDialogAdapter::RemoveDuplicateDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{

}

void RemoveDuplicateDialogAdapter::setupSpecificUIWidgets(QLayout* rootLayout)
{
    replaceOptionWidget(rootLayout, new RemoveDuplicateDialogOptionWidget(rootLayout->parentWidget()));
    replaceSaveWidget(rootLayout, new OtoFileSaveWidgetWithSecondFileNameAsDeleted(rootLayout->parentWidget()));
}

bool RemoveDuplicateDialogAdapter::doWorkAdapter(const OtoEntryList& otoList, OtoEntryList& otoListWorking, OtoEntryList& secondSaveList, const ToolOptions* abstractOptions, QWidget* dialogParent)
{
    auto options = qobject_cast<const RemoveDuplicateOptions*>(abstractOptions);

    QStringList compareStringList;
    for (int i = 0; i < otoList.count(); ++i)
    {
        compareStringList.append(otoList.at(i).alias());
    }

    //处理特定后缀
    QHash<int, QString> removedSpecificSuffixMap; //为整理时添加回特定后缀留存
    if (options->ignoreSpecificSuffix){
        for (int i = 0; i < otoList.count(); ++i)
        {
            for (const auto& currentItem : options->suffixList)
            {
                if (compareStringList.at(i).endsWith(currentItem))
                {
                    auto result = OtoEntryFunctions::removeSuffix(compareStringList.at(i), currentItem);
                    compareStringList.replace(i, result);
                    removedSpecificSuffixMap.insert(i, currentItem);
                }
            }
        }
    }
    //处理音高后缀
    //auto isIgnorePitchSuffix = ui->ignorePitchSuffixCheckBox->isChecked();
    QHash<int, QString> removedPitchStringList; //为整理时添加回音高后缀留存
    if (options->ignorePitchSuffix)
        for (int i = 0; i < otoList.count(); ++i)
        {
            QString removedPitch {};
            auto result = OtoEntryFunctions::removePitchSuffix(compareStringList.at(i), options->bottomPitch, options->topPitch,
                                                               options->pitchCaseSensitive,
                                                               options->pitchCase, &removedPitch);
            compareStringList.replace(i, result);
            if (!removedPitch.isEmpty())
                removedPitchStringList.insert(i, removedPitch);
        }

    //处理数字后缀（重复）
    QStringList digitSuffixList;
    for (int i = 0; i < otoList.count(); ++i)
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
    if (options->shouldOrganize){
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
                                (i > 0 ? QString::number((options->organizeStartFrom1 ? i : i + 1)) : "") +
                                (options->pitchCaseOrganized == OtoEntryFunctions::Upper ? removedPitchStringList.value(currentID, "").toUpper() : removedPitchStringList.value(currentID, "").toLower()) +
                                removedSpecificSuffixMap.value(currentID, ""));
            }
        }
        auto model = new OtoListShowValueChangeModel(&otoList, &otoListWorking, OtoEntry::Alias, this);
        auto askDialog = new ShowOtoListDialog(model, dialogParent);
        askDialog->setWindowTitle(tr("重复项整理结果"));
        askDialog->setLabel(tr("以下特别标出的原音设定的别名将会被重命名，其中多余的重复项将根据您的设置在下一步被删除。点击“确定”来确认此修改，点击“取消”以取消本次操作。"));
        askDialog->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

#ifdef SHINE5402OTOBOX_TEST
        QTimer::singleShot(0, askDialog, &ShowOtoListDialog::accept);
#endif
        auto shouldOrganize = askDialog->exec();
        if (shouldOrganize == QDialog::Rejected)
            return false;

        for (auto currentID : newAlias.keys())
        {
            auto currentEntry = otoListWorking.at(currentID);
            currentEntry.setAlias(newAlias.value(currentID));
            otoListWorking.replace(currentID, currentEntry);
        }
    }

    //删除重复项
    //检查重复并确认待删除项
    if (options->maxDuplicateCount != 0) {
        QList<int> toBeRemoved;

        for (auto key : compareStringMap.uniqueKeys())
        {
            if (compareStringMap.count(key) > options->maxDuplicateCount)
            {
                auto values = compareStringMap.values(key);
                std::sort(values.begin(), values.end());
                toBeRemoved.append(values.mid(options->maxDuplicateCount));
            }
        }
        std::sort(toBeRemoved.begin(), toBeRemoved.end());
        OtoEntryList toBeRemovedOtoList;
        for (auto i : toBeRemoved)
        {
            toBeRemovedOtoList.append(otoListWorking.at(i));
        }
        auto askDialog = new ShowOtoListDialog(&toBeRemovedOtoList, dialogParent);
        askDialog->setWindowTitle(tr("要被删除的原音设定条目列表"));
        askDialog->setLabel(tr("以下 %1 条原音设定条目将会被删除，或是被保存到您指定的文件中。点击“确定”来确认此修改，点击“取消”以取消本次操作。").arg(toBeRemoved.count()));
        askDialog->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

#ifdef SHINE5402OTOBOX_TEST
        QTimer::singleShot(0, askDialog, &ShowOtoListDialog::accept);
#endif

        auto shouldDelete = askDialog->exec();
        if (shouldDelete == QDialog::Rejected)
            return false;

        secondSaveList = toBeRemovedOtoList;

        for (auto i : toBeRemovedOtoList){
            otoListWorking.removeOne(i);
        }
    }

    return true;
}

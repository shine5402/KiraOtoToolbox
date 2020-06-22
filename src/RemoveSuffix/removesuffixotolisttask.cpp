#include "removesuffixotolisttask.h"

RemoveSuffixOtoListTask::RemoveSuffixOtoListTask(QObject* parent) : OtoListTask(parent)
{

}

bool RemoveSuffixOtoListTask::doTask(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* options)
{
    QStringList aliasList;
    for (int i = 0; i < srcOtoList.count(); ++i)
    {
        aliasList.append(srcOtoList.at(i).alias());
    }
    //处理特定后缀
    QHash<int, QString> removedSpecificSuffixMap; //为整理时添加回特定后缀留存
    if (options->getOption("ignoreSpecificSuffix").toBool()){
        for (int i = 0; i < srcOtoList.count(); ++i)
        {
            for (const auto& currentItem : options->getOption("suffixList").toStringList())
            {
                if (aliasList.at(i).endsWith(currentItem))
                {
                    auto result = OtoEntryFunctions::removeSuffix(aliasList.at(i), currentItem);
                    aliasList.replace(i, result);
                    removedSpecificSuffixMap.insert(i, currentItem);
                }
            }
        }
    }
    //处理音高后缀
    //auto isIgnorePitchSuffix = ui->ignorePitchSuffixCheckBox->isChecked();
    QHash<int, QString> removedPitchStringList; //为整理时添加回音高后缀留存
    if (options->getOption("ignorePitchSuffix").toBool())
        for (int i = 0; i < srcOtoList.count(); ++i)
        {
            QString removedPitch {};
            auto result = OtoEntryFunctions::removePitchSuffix(aliasList.at(i), options->getOption("bottomPitch").toString(), options->getOption("topPitch").toString(),
                                                               options->getOption("pitchCaseSensitive", Qt::CaseInsensitive).value<Qt::CaseSensitivity>(),
                                                               static_cast<OtoEntryFunctions::CharacterCase>(options->getOption("pitchCase").toInt()), &removedPitch);
            aliasList.replace(i, result);
            if (!removedPitch.isEmpty())
                removedPitchStringList.insert(i, removedPitch);
        }

}

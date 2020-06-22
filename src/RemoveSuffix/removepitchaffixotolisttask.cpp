#include "removepitchaffixotolisttask.h"

RemovePitchAffixOtoListTask::RemovePitchAffixOtoListTask(QObject* parent) : OtoListTask(parent)
{

}

bool RemovePitchAffixOtoListTask::doTask(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* options)
{
    Q_UNUSED(secondSaveOtoList);
    removedPitchStringList.clear();
    std::function<decltype (OtoEntryFunctions::removePitchPrefix)> removeFunc{};
    auto func = [&](){
        for (int i = 0; i < srcOtoList.count(); ++i)
    {
        auto& currentOto = resultOtoList[i];
        QString removedPitch {};
        auto result = removeFunc(currentOto.alias(), options->getOption("bottomPitch").toString(), options->getOption("topPitch").toString(),
                                                           options->getOption("pitchCaseSensitive", Qt::CaseInsensitive).value<Qt::CaseSensitivity>(),
                                                           static_cast<OtoEntryFunctions::CharacterCase>(options->getOption("pitchCase").toInt()), &removedPitch);
        currentOto.setAlias(result);
        if (!removedPitch.isEmpty())
            removedPitchStringList.insert(i, removedPitch);
    }
    };

    if (options->getOption("removePitchPrefix").toBool()){
        removeFunc = OtoEntryFunctions::removePitchPrefix;
        func();
    }

    if (options->getOption("removePitchSuffix").toBool()){
        removeFunc = OtoEntryFunctions::removePitchSuffix;
        func();
    }

    return removeFunc.operator bool();
}

QHash<int, QString> RemovePitchAffixOtoListTask::getRemovedPitchStringList() const
{
    return removedPitchStringList;
}

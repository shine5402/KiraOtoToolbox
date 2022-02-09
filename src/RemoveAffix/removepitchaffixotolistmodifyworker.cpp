#include "removepitchaffixotolistmodifyworker.h"

RemovePitchAffixOtoListModifyWorker::RemovePitchAffixOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

void RemovePitchAffixOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList);
    resultOtoList = srcOtoList;
    removedStringInfos.clear();
    std::function<decltype (OtoEntryFunctions::removePitchPrefix)> removeFunc{};
    auto func = [&](RemovedStringInfo::AffixType affixType) {
        for (int i = 0; i < srcOtoList.count(); ++i)
    {
        auto& currentOto = resultOtoList[i];
        QString removedPitch {};
        auto result = removeFunc(currentOto.alias(), options.getOption("bottomPitch").toString(), options.getOption("topPitch").toString(),
                                                           options.getOption("pitchCaseSensitive", Qt::CaseInsensitive).value<Qt::CaseSensitivity>(),
                                                           options.getOption("pitchCase").value<OtoEntryFunctions::CharacterCase>(), &removedPitch);
        currentOto.setAlias(result);
        removedStringInfos.append(RemovedStringInfo(affixType, i, removedPitch));
    }
    };

    Q_ASSERT(options.getOption("removePitchPrefix").toBool() || options.getOption("removePitchSuffix").toBool());

    if (options.getOption("removePitchPrefix").toBool()){
        removeFunc = OtoEntryFunctions::removePitchPrefix;
        func(RemovedStringInfo::Prefix);
    }

    if (options.getOption("removePitchSuffix").toBool()){
        removeFunc = OtoEntryFunctions::removePitchSuffix;
        func(RemovedStringInfo::Suffix);
    }
}

QVector<RemovedStringInfo> RemovePitchAffixOtoListModifyWorker::getRemovedStringInfos() const
{
    return removedStringInfos;
}

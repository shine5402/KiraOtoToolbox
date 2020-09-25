#include "removepitchaffixotolistmodifyworker.h"

RemovePitchAffixOtoListModifyWorker::RemovePitchAffixOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

bool RemovePitchAffixOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions& options)
{
    Q_UNUSED(secondSaveOtoList);
    resultOtoList = srcOtoList;
    removedStringInfos.clear();
    std::function<decltype (OtoEntryFunctions::removePitchPrefix)> removeFunc{};
    auto func = [&](RemovedStringInfo::AffixType affixType) {//return 被删除的字符串
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

    if (options.getOption("removePitchPrefix").toBool()){
        removeFunc = OtoEntryFunctions::removePitchPrefix;
        func(RemovedStringInfo::Prefix);
    }

    if (options.getOption("removePitchSuffix").toBool()){
        removeFunc = OtoEntryFunctions::removePitchSuffix;
        func(RemovedStringInfo::Suffix);
    }
    return removeFunc.operator bool();
}

QVector<RemovedStringInfo> RemovePitchAffixOtoListModifyWorker::getRemovedStringInfos() const
{
    return removedStringInfos;
}

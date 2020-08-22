#include "removepitchaffixotolistmodifyworker.h"

RemovePitchAffixOtoListModifyWorker::RemovePitchAffixOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

bool RemovePitchAffixOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions& options)
{
    Q_UNUSED(secondSaveOtoList);
    removedStringInfos.clear();
    std::function<decltype (OtoEntryFunctions::removePitchPrefix)> removeFunc{};
    auto func = [&]() -> QPair<int, QString> {//return 被删除的字符串
        for (int i = 0; i < srcOtoList.count(); ++i)
    {
        auto& currentOto = resultOtoList[i];
        QString removedPitch {};
        auto result = removeFunc(currentOto.alias(), options.getOption("bottomPitch").toString(), options.getOption("topPitch").toString(),
                                                           options.getOption("pitchCaseSensitive", Qt::CaseInsensitive).value<Qt::CaseSensitivity>(),
                                                           static_cast<OtoEntryFunctions::CharacterCase>(options.getOption("pitchCase").toInt()), &removedPitch);
        currentOto.setAlias(result);
        return {i, removedPitch};
    }
        return {-1, {}};
    };

    if (options.getOption("removePitchPrefix").toBool()){
        removeFunc = OtoEntryFunctions::removePitchPrefix;
        auto removed = func();
        if (!(removed.first != -1))
        {
            removedStringInfos.append(RemovedStringInfo(RemovedStringInfo::Prefix, removed.first, removed.second));
        }
    }

    if (options.getOption("removePitchSuffix").toBool()){
        removeFunc = OtoEntryFunctions::removePitchSuffix;
        auto removed = func();
        if (!(removed.first != -1))
        {
            removedStringInfos.append(RemovedStringInfo(RemovedStringInfo::Suffix, removed.first, removed.second));
        }
    }
    return removeFunc.operator bool();
}

QVector<RemovedStringInfo> RemovePitchAffixOtoListModifyWorker::getRemovedStringInfos() const
{
    return removedStringInfos;
}

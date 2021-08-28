#include "removeduplicatemoduleotolistmodifyworker.h"
#include "removeAffix/removeaffixotolistmodifyworker.h"
#include "orgnaizeduplicateotolistmodifyworker.h"
#include "removeduplicateotolistmodifyworker.h"
#include "removeAffix/removespecificaffixotolistmodifyworker.h"
#include "removeAffix/removepitchaffixotolistmodifyworker.h"


RemoveDuplicateModuleOtoListModifyWorker::RemoveDuplicateModuleOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

bool RemoveDuplicateModuleOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    OtoEntryList lastResult = srcOtoList;
    OtoEntryList currentResult;
    bool success = false;

    auto updateResult = [&](){
        lastResult = std::move(currentResult);
        currentResult = {};
    };

    RemoveAffixOtoListModifyWorker removeAffixWorker;
    success |= removeAffixWorker.doWork(lastResult, currentResult, secondSaveOtoList, options.extract("affixRemove/"));
    updateResult();

    if (options.getOption("shouldOrganize").toBool()){
        OrgnaizeDuplicateOtoListModifyWorker orgnaizeWorker;
        success |= orgnaizeWorker.doWork(lastResult, currentResult, secondSaveOtoList, options);
        organizeResult = currentResult;
        updateResult();
    }

    //为之后加回被忽略词缀做准备
    auto beforeRemoveDuplicate = lastResult;

    RemoveDuplicateOtoListModifyWorker removeDuplicateWorker;
    success |= removeDuplicateWorker.doWork(lastResult, currentResult, secondSaveOtoList, options);

    //将词缀加回
    auto specificRemovedInfos = removeAffixWorker.getSpecificWorker()->getRemovedStringInfos();
    auto pitchRemovedInfos = removeAffixWorker.getPitchWorker()->getRemovedStringInfos();
    for (auto& i : (pitchRemovedInfos + specificRemovedInfos)){
        auto& currentOto = beforeRemoveDuplicate[i.id()];
        auto newAlias = [&]() -> QString{
                switch (i.type()) {
                case RemovedStringInfo::Prefix :{
                return i.value() + currentOto.alias();
    }
                case RemovedStringInfo::Suffix : {
                return currentOto.alias() + i.value();
    }
    }
                return {};
    }();
        currentOto.setAlias(newAlias);
    }

    updateResult();
    currentResult = beforeRemoveDuplicate;

    //重新删除重复项
    OtoEntryList toBeRemovedOtoList;
    auto removedID = removeDuplicateWorker.getRemovedIDs();
    for (auto i : std::as_const(removedID))
    {
        toBeRemovedOtoList.append(currentResult.at(i));
    }

    secondSaveOtoList = toBeRemovedOtoList;

    for (const auto& i : std::as_const(toBeRemovedOtoList)){
        currentResult.removeOne(i);
    }

    resultOtoList = currentResult;
    return success;
}

OtoEntryList RemoveDuplicateModuleOtoListModifyWorker::getOrganizeResult() const
{
    return organizeResult;
}

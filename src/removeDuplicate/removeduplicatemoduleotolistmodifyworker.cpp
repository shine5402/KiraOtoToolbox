#include "removeduplicatemoduleotolistmodifyworker.h"
#include "removeAffix/removeaffixotolistmodifyworker.h"
#include "orgnaizeduplicateotolistmodifyworker.h"
#include "removeduplicateotolistmodifyworker.h"
#include "removeAffix/removespecificaffixotolistmodifyworker.h"
#include "removeAffix/removepitchaffixotolistmodifyworker.h"


RemoveDuplicateModuleOtoListModifyWorker::RemoveDuplicateModuleOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

void RemoveDuplicateModuleOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    OtoEntryList lastResult = srcOtoList;
    OtoEntryList currentResult;

    auto updateResult = [&](){
        lastResult = std::move(currentResult);
        currentResult = {};
    };

    RemoveAffixOtoListModifyWorker removeAffixWorker;
    removeAffixWorker.doWork(lastResult, currentResult, secondSaveOtoList, options.extract("affixRemove/"));
    updateResult();

    if (options.getOption("shouldOrganize").toBool()){
        OrgnaizeDuplicateOtoListModifyWorker orgnaizeWorker;
        orgnaizeWorker.doWork(lastResult, currentResult, secondSaveOtoList, options);
        organizeResult = currentResult;
        updateResult();
    }

    //Prepare for add affix later
    auto beforeRemoveDuplicate = lastResult;

    RemoveDuplicateOtoListModifyWorker removeDuplicateWorker;
    removeDuplicateWorker.doWork(lastResult, currentResult, secondSaveOtoList, options);

    //Add affix back
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

    //Remove duplicated entries
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
}

OtoEntryList RemoveDuplicateModuleOtoListModifyWorker::getOrganizeResult() const
{
    return organizeResult;
}

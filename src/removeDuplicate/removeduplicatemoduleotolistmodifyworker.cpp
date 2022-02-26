#include "removeduplicatemoduleotolistmodifyworker.h"
#include "removeAffix/removeaffixotolistmodifyworker.h"
#include "orgnaizeduplicateotolistmodifyworker.h"
#include "removeduplicateotolistmodifyworker.h"
#include "removeAffix/removespecificaffixotolistmodifyworker.h"
#include "removeAffix/removepitchaffixotolistmodifyworker.h"
#include "utils/misc/misc.h"


RemoveDuplicateModuleOtoListModifyWorker::RemoveDuplicateModuleOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

void RemoveDuplicateModuleOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    //For confirm msg dialog
    this->srcOtoList = srcOtoList;
    precision = options.getOption("save/precision").toInt();

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
    toBeRemovedOtoList.clear();
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

bool RemoveDuplicateModuleOtoListModifyWorker::needConfirm() const
{
    return (!organizeResult.isEmpty()) || (!toBeRemovedOtoList.isEmpty());
}

QVector<OtoListModifyWorker::ConfirmMsg> RemoveDuplicateModuleOtoListModifyWorker::getConfirmMsgs() const
{
    QVector<OtoListModifyWorker::ConfirmMsg> result;
    if (!organizeResult.isEmpty())
    {
        result.append({Dialog,
                       tr("Result of organizing duplicate entries"),
                       std::shared_ptr<QDialog>(Misc::getOtoDiffDialog(srcOtoList, organizeResult, precision, tr("Result of organizing duplicate entries"),
                       tr("The emphasized entries will be renamed, in which unneeded ones will be removed in next step. Click \"OK\" to confirm, \"Cancel\" to discard these changes."),
                       nullptr,
                       Misc::ValueChangeModel))});
    }

    if (!toBeRemovedOtoList.isEmpty()){
        result.append({Dialog,
                      tr("Oto entries to remove"),
                      std::shared_ptr<QDialog>(Misc::getAskUserWithShowOtoListDialog(toBeRemovedOtoList, tr("Oto entries to remove"),
                       tr("These %1 oto entries will be removed, or be saved to the specified file. Click \"OK\" to confirm, \"Cancel\" to discard these changes.").arg(toBeRemovedOtoList.count()),
                       nullptr))});
    }

    return result;
}

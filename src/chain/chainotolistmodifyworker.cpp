#include "chainotolistmodifyworker.h"
#include "toolBase/toolmanager.h"
#include "chainelement.h"

ChainOtoListModifyWorker::ChainOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

void ChainOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    OtoEntryList lastResult = srcOtoList;
    OtoEntryList& currentResult = resultOtoList;

    auto saveOptions = options.extract("save/");
    auto fileName = options.getOption("load/fileName");
    auto steps = options.getOption("steps").value<QVector<ChainElement>>();

    for (int i = 0; i < steps.count(); ++i){
        const auto& step = steps.at(i);
        auto stepOption = step.options;
        stepOption.combine(saveOptions, "save/");
        stepOption.setOption("load/fileName", fileName);
        try {
            auto worker = std::shared_ptr(step.tool.getWorkerInstance());
            worker->doWork(lastResult, currentResult, secondSaveOtoList, stepOption);
            if (worker->needConfirm())
                needConfirmWorkers.append(worker);
        }
        catch (const ToolException& e){
            throw ToolException(tr("Error occured at step %1 (%2): %3.").arg(i).arg(step.toolName(), e.info()));
        }
        catch (...){
            throw ToolException(tr("Unknown error occured at step %1 (%2).").arg(i).arg(step.toolName()));
        }

        lastResult = std::move(currentResult);
        currentResult = {};
    }

    resultOtoList = lastResult;
}

bool ChainOtoListModifyWorker::needConfirm() const
{
    return true;
}


QVector<OtoListModifyWorker::ConfirmMsg> ChainOtoListModifyWorker::getConfirmMsgs() const
{
    QVector<OtoListModifyWorker::ConfirmMsg> result;
    for (const auto& worker : qAsConst(needConfirmWorkers)){
        result.append(worker->getConfirmMsgs());
    }
    return result;
}

bool ChainOtoListModifyWorker::isConfirmDialogAccepted(int msgTypeId, int dialogResult) const
{
    if (msgTypeId == Dialog || msgTypeId == MessageBox)
        return OtoListModifyWorker::isConfirmDialogAccepted(msgTypeId, dialogResult);

    auto worker = fplus::find_first_by([](const std::shared_ptr<OtoListModifyWorker>& worker){
        return fplus::find_first_by([](const ConfirmMsg& msg){
            return msg.typeId();
        }, worker->getConfirmMsgs()).is_just();
    }, needConfirmWorkers);
    if (worker.is_just())
        return worker.unsafe_get_just()->isConfirmDialogAccepted(msgTypeId, dialogResult);
    return false;
}

void ChainOtoListModifyWorker::commit()
{
    for (const auto& worker : qAsConst(needConfirmWorkers)){
        worker->commit();
    }
}

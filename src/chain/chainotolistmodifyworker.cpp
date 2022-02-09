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

    auto steps = options.getOption("steps").value<QVector<ChainElement>>();

    for (int i = 0; i < steps.count(); ++i){
        const auto& step = steps.at(i);
        auto stepOption = step.options;
        try{
            step.tool.getWorkerInstance()->doWork(lastResult, currentResult, secondSaveOtoList, stepOption);
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

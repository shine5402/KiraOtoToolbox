#include "chainotolistmodifyworker.h"
#include "toolBase/toolmanager.h"
#include "chainelement.h"

ChainOtoListModifyWorker::ChainOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

bool ChainOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    OtoEntryList lastResult = srcOtoList;
    OtoEntryList& currentResult = resultOtoList;

    bool success = false;

    auto steps = options.getOption("steps").value<QVector<ChainElement>>();

    for (const auto& step : steps){
        auto stepOption = step.options;
        success |= step.tool.getWorkerInstance()->doWork(lastResult, currentResult, secondSaveOtoList, stepOption);

        lastResult = std::move(currentResult);
        currentResult = {};
    }

    resultOtoList = lastResult;
    return success;
}

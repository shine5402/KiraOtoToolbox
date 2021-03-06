#include "chainotolistmodifyworker.h"
#include "toolBase/toolmanager.h"

ChainOtoListModifyWorker::ChainOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

bool ChainOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    OtoEntryList lastResult = srcOtoList;
    OtoEntryList& currentResult = resultOtoList;

    bool success = false;

    auto steps = options.getOption("steps").value<QVector<Tool>>();

    for (auto step : steps){
        auto stepOption = step.getOptionWidget()->getOptions();
        success |= step.getModifyWorker()->doWork(lastResult, currentResult, secondSaveOtoList, stepOption);

        lastResult = std::move(currentResult);
        currentResult = {};
    }

    resultOtoList = lastResult;
    return success;
}

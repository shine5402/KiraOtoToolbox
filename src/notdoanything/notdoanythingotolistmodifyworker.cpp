#include "notdoanythingotolistmodifyworker.h"

NotDoAnythingOtoListModifyWorker::NotDoAnythingOtoListModifyWorker(QObject *parent) : OtoListModifyWorker(parent)
{

}

void NotDoAnythingOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)
    Q_UNUSED(options)
    resultOtoList = srcOtoList;
}

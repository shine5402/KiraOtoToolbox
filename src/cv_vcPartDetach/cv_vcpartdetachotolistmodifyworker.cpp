#include "cv_vcpartdetachotolistmodifyworker.h"

CV_VCPartDetachOtoListModifyWorker::CV_VCPartDetachOtoListModifyWorker(QObject *parent) : OtoListModifyWorker(parent)
{

}

bool CV_VCPartDetachOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    auto isSeePatternAsCV = options.getOption("isSeePatternAsCV").toBool();
    auto seePatternAsCVContent = options.getOption("seePatternAsCVContent").toStringList();

}

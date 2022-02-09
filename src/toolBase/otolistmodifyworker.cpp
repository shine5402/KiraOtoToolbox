#include "otolistmodifyworker.h"
#include "utils/models/otolistmodel.h"
#include "utils/dialogs/showotolistdialog.h"

OtoListModifyWorker::OtoListModifyWorker(QObject *parent) : QObject(parent)
{

}

void OtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(srcOtoList)
    Q_UNUSED(resultOtoList)
    Q_UNUSED(secondSaveOtoList)
    Q_UNUSED(options)
    Q_ASSERT_X(false, "OtoListModifyWorker::doWork(Abstract)", "Not implemented");
    Q_UNREACHABLE();
}

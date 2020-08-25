#include "otolistmodifyworker.h"
#include "utils/models/otolistmodel.h"
#include "utils/dialogs/showotolistdialog.h"

OtoListModifyWorker::OtoListModifyWorker(QObject *parent) : QObject(parent)
{

}

bool OtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions& options)
{
    Q_UNUSED(srcOtoList)
    Q_UNUSED(resultOtoList)
    Q_UNUSED(secondSaveOtoList)
    Q_UNUSED(options)
    Q_ASSERT_X(false, "OtoListModifyWorker::doWork(Abstract)", "Not implemented");
}

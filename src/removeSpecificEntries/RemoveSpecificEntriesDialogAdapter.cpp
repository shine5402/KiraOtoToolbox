#include "RemoveSpecificEntriesDialogAdapter.h"

#include "RemoveSpecificEntriesOptionWidget.h"
#include "RemoveSpecificEntriesOtoListModifyWorker.h"

RemoveSpecificEntriesDialogAdapter::RemoveSpecificEntriesDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(RemoveSpecificEntriesOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(RemoveSpecificEntriesOptionWidget::staticMetaObject);
}

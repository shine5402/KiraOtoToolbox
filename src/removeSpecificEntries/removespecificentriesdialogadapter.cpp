#include "removespecificentriesdialogadapter.h"
#include "removespecificentriesoptionwidget.h"
#include "removespecificentriesotolistmodifyworker.h"

RemoveSpecificEntriesDialogAdapter::RemoveSpecificEntriesDialogAdapter(QObject* parent):
    ToolDialogAdapter(parent)
{
    setWorkerMetaObj(RemoveSpecificEntriesOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(RemoveSpecificEntriesOptionWidget::staticMetaObject);
}

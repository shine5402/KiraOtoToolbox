#include "mergeotodialogadapter.h"
#include "mergeotooptionwidget.h"
#include "mergeotootolistmodifyworker.h"

MergeOtoDialogAdapter::MergeOtoDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setOptionWidgetMetaObj(MergeOtoOptionWidget::staticMetaObject);
    setWorkerMetaObj(MergeOtoOtoListModifyWorker::staticMetaObject);
}

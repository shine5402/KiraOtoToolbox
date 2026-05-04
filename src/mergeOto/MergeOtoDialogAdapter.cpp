#include "MergeOtoDialogAdapter.h"

#include "MergeOtoOptionWidget.h"
#include "MergeOtoOtoListModifyWorker.h"

MergeOtoDialogAdapter::MergeOtoDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setOptionWidgetMetaObj(MergeOtoOptionWidget::staticMetaObject);
    setWorkerMetaObj(MergeOtoOtoListModifyWorker::staticMetaObject);
}

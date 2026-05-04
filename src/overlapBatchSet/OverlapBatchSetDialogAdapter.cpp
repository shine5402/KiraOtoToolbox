#include "OverlapBatchSetDialogAdapter.h"

#include "OverlapBatchSetDialogOptionWidget.h"
#include "OverlapBatchSetOtoListModifyWorker.h"

OverlapBatchSetDialogAdapter::OverlapBatchSetDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(OverlapBatchSetOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(OverlapBatchSetDialogOptionWidget::staticMetaObject);
}

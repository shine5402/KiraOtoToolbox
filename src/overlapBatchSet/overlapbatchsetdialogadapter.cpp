#include "overlapbatchsetdialogadapter.h"
#include "overlapbatchsetdialogoptionwidget.h"
#include "overlapbatchsetotolistmodifyworker.h"

OverlapBatchSetDialogAdapter::OverlapBatchSetDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(OverlapBatchSetOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(OverlapBatchSetDialogOptionWidget::staticMetaObject);
}

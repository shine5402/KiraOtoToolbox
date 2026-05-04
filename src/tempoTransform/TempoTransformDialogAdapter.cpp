#include "TempoTransformDialogAdapter.h"
#include "TempoTransformOptionWidget.h"
#include "TempoTransformOtoListModifyWorker.h"

TempoTransformDialogAdapter::TempoTransformDialogAdapter(QObject *parent)
    : ToolDialogAdapter{parent}
{
    setOptionWidgetMetaObj(TempoTransformOptionWidget::staticMetaObject);
    setWorkerMetaObj(TempoTransformOtoListModifyWorker::staticMetaObject);
}

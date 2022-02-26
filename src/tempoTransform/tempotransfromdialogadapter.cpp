#include "tempotransfromdialogadapter.h"
#include "tempotransformoptionwidget.h"
#include "tempotransformotolistmodifyworker.h"

TempoTransformDialogAdapter::TempoTransformDialogAdapter(QObject *parent)
    : ToolDialogAdapter{parent}
{
    setOptionWidgetMetaObj(TempoTransformOptionWidget::staticMetaObject);
    setWorkerMetaObj(TempoTransformOtoListModifyWorker::staticMetaObject);
}

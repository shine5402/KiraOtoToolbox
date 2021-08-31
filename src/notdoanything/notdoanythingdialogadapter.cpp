#include "notdoanythingdialogadapter.h"
#include "notdoanythingotolistmodifyworker.h"
#include "notdoanythingoptionwidget.h"

NotDoAnythingDialogAdapter::NotDoAnythingDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(NotDoAnythingOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(NotDoAnythingOptionWidget::staticMetaObject);
}

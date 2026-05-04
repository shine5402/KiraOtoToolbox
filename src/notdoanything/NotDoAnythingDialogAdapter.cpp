#include "NotDoAnythingDialogAdapter.h"
#include "NotDoAnythingOtoListModifyWorker.h"
#include "NotDoAnythingOptionWidget.h"

NotDoAnythingDialogAdapter::NotDoAnythingDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(NotDoAnythingOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(NotDoAnythingOptionWidget::staticMetaObject);
}

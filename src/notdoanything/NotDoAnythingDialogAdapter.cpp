#include "NotDoAnythingDialogAdapter.h"

#include "NotDoAnythingOptionWidget.h"
#include "NotDoAnythingOtoListModifyWorker.h"

NotDoAnythingDialogAdapter::NotDoAnythingDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(NotDoAnythingOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(NotDoAnythingOptionWidget::staticMetaObject);
}

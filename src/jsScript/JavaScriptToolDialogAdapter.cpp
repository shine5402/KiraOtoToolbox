#include "JavaScriptToolDialogAdapter.h"

#include "JavaScriptToolOptionWidget.h"
#include "JavaScriptToolOtoListModifyWorker.h"

JavaScriptToolDialogAdapter::JavaScriptToolDialogAdapter(QObject *parent) : ToolDialogAdapter{parent}
{
    setOptionWidgetMetaObj(JavaScriptToolOptionWidget::staticMetaObject);
    setWorkerMetaObj(JavaScriptToolOtoListModifyWorker::staticMetaObject);
}

#include "javascripttooldialogadapter.h"
#include "javascripttooloptionwidget.h"
#include "javascripttoolotolistmodifyworker.h"

JavaScriptToolDialogAdapter::JavaScriptToolDialogAdapter(QObject *parent)
    : ToolDialogAdapter{parent}
{
    setOptionWidgetMetaObj(JavaScriptToolOptionWidget::staticMetaObject);
    setWorkerMetaObj(JavaScriptToolOtoListModifyWorker::staticMetaObject);
}

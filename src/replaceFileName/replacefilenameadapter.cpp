#include "replacefilenameadapter.h"
#include "replacefilenameoptionwidget.h"
#include "replacefilenameotolistmodifyworker.h"

ReplaceFileNameAdapter::ReplaceFileNameAdapter(QObject *parent)
    : ToolDialogAdapter{parent}
{
    setOptionWidgetMetaObj(ReplaceFileNameOptionWidget::staticMetaObject);
    setWorkerMetaObj(ReplaceFileNameOtoListModifyWorker::staticMetaObject);
}

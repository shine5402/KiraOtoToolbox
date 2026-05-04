#include "ReplaceFileNameAdapter.h"
#include "ReplaceFileNameOptionWidget.h"
#include "ReplaceFileNameOtoListModifyWorker.h"

ReplaceFileNameAdapter::ReplaceFileNameAdapter(QObject *parent)
    : ToolDialogAdapter{parent}
{
    setOptionWidgetMetaObj(ReplaceFileNameOptionWidget::staticMetaObject);
    setWorkerMetaObj(ReplaceFileNameOtoListModifyWorker::staticMetaObject);
}

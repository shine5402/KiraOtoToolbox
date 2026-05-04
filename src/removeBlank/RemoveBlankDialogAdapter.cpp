#include "RemoveBlankDialogAdapter.h"

#include "RemoveBlankOptionWidget.h"
#include "RemoveBlankOtoListModifyWorker.h"

RemoveBlankDialogAdapter::RemoveBlankDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(RemoveBlankOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(RemoveBlankOptionWidget::staticMetaObject);
}

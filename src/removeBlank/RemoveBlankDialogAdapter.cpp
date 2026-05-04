#include "RemoveBlankDialogAdapter.h"
#include "RemoveBlankOtoListModifyWorker.h"
#include "RemoveBlankOptionWidget.h"

RemoveBlankDialogAdapter::RemoveBlankDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(RemoveBlankOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(RemoveBlankOptionWidget::staticMetaObject);
}

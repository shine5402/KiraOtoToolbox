#include "RemoveAffixDialogAdapter.h"
#include "RemoveAffixOptionWidget.h"
#include "RemoveAffixOtoListModifyWorker.h"

RemoveAffixDialogAdapter::RemoveAffixDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(RemoveAffixOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(RemoveAffixOptionWidget::staticMetaObject);
}

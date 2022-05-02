#include "removeaffixdialogadapter.h"
#include "removeaffixoptionwidget.h"
#include "removeaffixotolistmodifyworker.h"

RemoveAffixDialogAdapter::RemoveAffixDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(RemoveAffixOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(RemoveAffixOptionWidget::staticMetaObject);
}

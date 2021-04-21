#include "removeaffixdialogadapter.h"
#include "removeaffixoptionwidget.h"
#include "removeaffixotolistmodifyworker.h"

RemoveAffixDialogAdapter::RemoveAffixDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(RemoveAffixOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(RemoveAffixOptionWidget::staticMetaObject);
}

QString RemoveAffixDialogAdapter::getToolName() const
{
    return tr("去除别名前/后缀");
}

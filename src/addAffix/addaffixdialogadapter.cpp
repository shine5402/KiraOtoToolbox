#include "addaffixdialogadapter.h"
#include "addaffixoptionwidget.h"
#include "addaffixotolistmodifyworker.h"

AddAffixDialogAdapter::AddAffixDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(AddAffixOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(AddAffixOptionWidget::staticMetaObject);
}


QString AddAffixDialogAdapter::getToolName() const
{
    return tr("添加别名前/后缀");
}

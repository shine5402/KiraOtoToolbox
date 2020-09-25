#include "addaffixdialogadapter.h"
#include "addaffixoptionwidget.h"
#include "addaffixotolistmodifyworker.h"

AddAffixDialogAdapter::AddAffixDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorker(new AddAffixOtoListModifyWorker(this));
    setOptionWidget(new AddAffixOptionWidget);
}


QString AddAffixDialogAdapter::getToolName() const
{
    return tr("添加别名前/后缀");
}

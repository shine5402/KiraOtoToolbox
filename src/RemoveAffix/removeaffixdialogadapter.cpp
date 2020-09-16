#include "removeaffixdialogadapter.h"
#include "removeaffixoptionwidget.h"
#include "removeaffixotolistmodifyworker.h"

RemoveAffixDialogAdapter::RemoveAffixDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorker(new RemoveAffixOtoListModifyWorker(this));
    setOptionWidget(new RemoveAffixOptionWidget);
}

QString RemoveAffixDialogAdapter::getToolName() const
{
    return tr("去除别名前/后缀");
}


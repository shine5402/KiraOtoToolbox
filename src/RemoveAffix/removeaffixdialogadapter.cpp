#include "removeaffixdialogadapter.h"
#include "removeaffixoptionwidget.h"
#include "removeaffixotolistmodifyworker.h"

RemoveAffixDialogAdapter::RemoveAffixDialogAdapter(QWidget* parent) : ToolDialogAdapter(parent)
{
    setWorker(new RemoveAffixOtoListModifyWorker(this));
}

void RemoveAffixDialogAdapter::setupSpecificUIWidgets(QLayout* rootLayout)
{
    replaceOptionWidget(rootLayout, new RemoveAffixOptionWidget(rootLayout->parentWidget()));
}

QString RemoveAffixDialogAdapter::getWindowTitle() const
{
    return tr("去除别名前/后缀");
}


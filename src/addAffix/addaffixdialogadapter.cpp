#include "addaffixdialogadapter.h"
#include "addaffixoptionwidget.h"
#include "addaffixotolistmodifyworker.h"

AddAffixDialogAdapter::AddAffixDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorker(new AddAffixOtoListModifyWorker(this));
}

void AddAffixDialogAdapter::setupSpecificUIWidgets(QLayout* rootLayout)
{
    replaceOptionWidget(rootLayout, new AddAffixOptionWidget(rootLayout->parentWidget()));
}

QString AddAffixDialogAdapter::getWindowTitle() const
{
    return tr("添加别名前/后缀");
}

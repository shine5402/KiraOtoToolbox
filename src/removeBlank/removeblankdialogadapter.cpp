#include "removeblankdialogadapter.h"
#include "removeblankotolistmodifyworker.h"
#include "removeblankoptionwidget.h"

RemoveBlankDialogAdapter::RemoveBlankDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorker(new RemoveBlankOtoListModifyWorker(this));
}

void RemoveBlankDialogAdapter::setupSpecificUIWidgets(QLayout* rootLayout)
{
    replaceOptionWidget(rootLayout, new RemoveBlankOptionWidget(rootLayout->parentWidget()));
}

QString RemoveBlankDialogAdapter::getWindowTitle() const
{
    return tr("清除空白项");
}

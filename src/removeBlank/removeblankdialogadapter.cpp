#include "removeblankdialogadapter.h"
#include "removeblankotolistmodifyworker.h"
#include "removeblankoptionwidget.h"

RemoveBlankDialogAdapter::RemoveBlankDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorker(new RemoveBlankOtoListModifyWorker(this));
    setOptionWidget(new RemoveBlankOptionWidget);
}

QString RemoveBlankDialogAdapter::getToolName() const
{
    return tr("清除空白项");
}

#include "notdoanythingdialogadapter.h"
#include "notdoanythingotolistmodifyworker.h"
#include "notdoanythingoptionwidget.h"

NotDoAnythingDialogAdapter::NotDoAnythingDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorker(new NotDoAnythingOtoListModifyWorker(this));
    setOptionWidget(new NotDoAnythingOptionWidget);
}

QString NotDoAnythingDialogAdapter::getToolName() const
{
    return tr("什么都不做");
}

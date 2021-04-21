#include "notdoanythingdialogadapter.h"
#include "notdoanythingotolistmodifyworker.h"
#include "notdoanythingoptionwidget.h"

NotDoAnythingDialogAdapter::NotDoAnythingDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(NotDoAnythingOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(NotDoAnythingOptionWidget::staticMetaObject);
}

QString NotDoAnythingDialogAdapter::getToolName() const
{
    return tr("什么都不做");
}

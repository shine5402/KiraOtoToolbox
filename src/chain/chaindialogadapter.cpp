#include "chaindialogadapter.h"
#include "chainotolistmodifyworker.h"
#include "chaintooloptionwidget.h"

ChainDialogAdapter::ChainDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(ChainOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(ChainToolOptionWidget::staticMetaObject);
}

QString ChainDialogAdapter::getToolName() const
{
    return tr("进行多个操作");
}

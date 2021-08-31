#include "chaindialogadapter.h"
#include "chainotolistmodifyworker.h"
#include "chaintooloptionwidget.h"

ChainDialogAdapter::ChainDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(ChainOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(ChainToolOptionWidget::staticMetaObject);
}

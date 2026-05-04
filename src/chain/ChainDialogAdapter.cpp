#include "ChainDialogAdapter.h"

#include "ChainOtoListModifyWorker.h"
#include "ChainToolOptionWidget.h"

ChainDialogAdapter::ChainDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(ChainOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(ChainToolOptionWidget::staticMetaObject);
}

#include "SetAliasDialogAdapter.h"
#include "SetAliasOtoListModifyWorker.h"
#include "SetAliasOptionWidget.h"

SetAliasDialogAdapter::SetAliasDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(SetAliasOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(SetAliasOptionWidget::staticMetaObject);
}

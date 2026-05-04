#include "SetAliasDialogAdapter.h"

#include "SetAliasOptionWidget.h"
#include "SetAliasOtoListModifyWorker.h"

SetAliasDialogAdapter::SetAliasDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(SetAliasOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(SetAliasOptionWidget::staticMetaObject);
}

#include "setaliasdialogadapter.h"
#include "setaliasotolistmodifyworker.h"
#include "setaliasoptionwidget.h"

SetAliasDialogAdapter::SetAliasDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(SetAliasOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(SetAliasOptionWidget::staticMetaObject);
}

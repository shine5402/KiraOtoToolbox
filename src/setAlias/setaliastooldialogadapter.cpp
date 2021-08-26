#include "setaliastooldialogadapter.h"
#include "setaliasotolistmodifyworker.h"
#include "setaliastooloptionwidget.h"

SetAliasToolDialogAdapter::SetAliasToolDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(SetAliasOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(SetAliasToolOptionWidget::staticMetaObject);
}

QString SetAliasToolDialogAdapter::getToolName() const
{
    return tr("设置别名");
}

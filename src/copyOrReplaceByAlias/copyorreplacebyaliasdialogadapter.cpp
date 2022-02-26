#include "copyorreplacebyaliasdialogadapter.h"
#include "copyorreplacebyaliasoptionwidget.h"
#include "copyorreplacebyaliasotolistmodifyworker.h"

CopyOrReplaceByAliasDialogAdapter::CopyOrReplaceByAliasDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setOptionWidgetMetaObj(CopyOrReplaceByAliasOptionWidget::staticMetaObject);
    setWorkerMetaObj(CopyOrReplaceByAliasOtoListModifyWorker::staticMetaObject);
}

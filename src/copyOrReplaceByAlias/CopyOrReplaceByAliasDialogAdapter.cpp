#include "CopyOrReplaceByAliasDialogAdapter.h"
#include "CopyOrReplaceByAliasOptionWidget.h"
#include "CopyOrReplaceByAliasOtoListModifyWorker.h"

CopyOrReplaceByAliasDialogAdapter::CopyOrReplaceByAliasDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setOptionWidgetMetaObj(CopyOrReplaceByAliasOptionWidget::staticMetaObject);
    setWorkerMetaObj(CopyOrReplaceByAliasOtoListModifyWorker::staticMetaObject);
}

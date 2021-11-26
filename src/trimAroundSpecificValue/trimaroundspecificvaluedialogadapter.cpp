#include "trimaroundspecificvaluedialogadapter.h"
#include "trimarounfspecificvalueotolistmodifyworker.h"
#include "trimaroundspecificvalueoptionwidget.h"

TrimAroundSpecificValueDialogAdapter::TrimAroundSpecificValueDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(TrimArounfSpecificValueOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(TrimAroundSpecificValueOptionWidget::staticMetaObject);
}

#include "TrimAroundSpecificValueDialogAdapter.h"
#include "TrimAroundSpecificValueOtoListModifyWorker.h"
#include "TrimAroundSpecificValueOptionWidget.h"

TrimAroundSpecificValueDialogAdapter::TrimAroundSpecificValueDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(TrimAroundSpecificValueOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(TrimAroundSpecificValueOptionWidget::staticMetaObject);
}

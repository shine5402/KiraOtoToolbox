#include "TrimAroundSpecificValueDialogAdapter.h"

#include "TrimAroundSpecificValueOptionWidget.h"
#include "TrimAroundSpecificValueOtoListModifyWorker.h"

TrimAroundSpecificValueDialogAdapter::TrimAroundSpecificValueDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(TrimAroundSpecificValueOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(TrimAroundSpecificValueOptionWidget::staticMetaObject);
}

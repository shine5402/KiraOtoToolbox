#include "precenteredchangevalueadapter.h"
#include "precenteredchangevalueoptionwidget.h"
#include "precenteredchangevalueotolistmodifyworker.h"

PreCenteredChangeValueAdapter::PreCenteredChangeValueAdapter(QObject *parent)
    : ToolDialogAdapter{parent}
{
    setOptionWidgetMetaObj(PreCenteredChangeValueOptionWidget::staticMetaObject);
    setWorkerMetaObj(PreCenteredChangeValueOtoListModifyWorker::staticMetaObject);
}

#include "PreCenteredChangeValueAdapter.h"
#include "PreCenteredChangeValueOptionWidget.h"
#include "PreCenteredChangeValueOtoListModifyWorker.h"

PreCenteredChangeValueAdapter::PreCenteredChangeValueAdapter(QObject *parent)
    : ToolDialogAdapter{parent}
{
    setOptionWidgetMetaObj(PreCenteredChangeValueOptionWidget::staticMetaObject);
    setWorkerMetaObj(PreCenteredChangeValueOtoListModifyWorker::staticMetaObject);
}

#include "VowelCrossfadingDialogAdapter.h"

#include "VowelCrossfadingOptionWidget.h"
#include "VowelCrossfadingOtoListModifyWorker.h"

VowelCrossfadingDialogAdapter::VowelCrossfadingDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(VowelCrossfadingOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(VowelCrossfadingOptionWidget::staticMetaObject);
}

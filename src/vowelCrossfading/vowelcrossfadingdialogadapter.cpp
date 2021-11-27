#include "vowelcrossfadingdialogadapter.h"
#include "vowelcrossfadingoptionwidget.h"
#include "vowelcrossfadingotolistmodifyworker.h"

VowelCrossfadingDialogAdapter::VowelCrossfadingDialogAdapter(QObject* parent):ToolDialogAdapter(parent)
{
    setWorkerMetaObj(VowelCrossfadingOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(VowelCrossfadingOptionWidget::staticMetaObject);
}

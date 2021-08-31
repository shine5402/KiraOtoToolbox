#include "removeblankdialogadapter.h"
#include "removeblankotolistmodifyworker.h"
#include "removeblankoptionwidget.h"

RemoveBlankDialogAdapter::RemoveBlankDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(RemoveBlankOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(RemoveBlankOptionWidget::staticMetaObject);
}

#include "removeblankdialogadapter.h"
#include "removeblankotolistmodifyworker.h"
#include "removeblankoptionwidget.h"

RemoveBlankDialogAdapter::RemoveBlankDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(RemoveBlankOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(RemoveBlankOptionWidget::staticMetaObject);
}

QString RemoveBlankDialogAdapter::getToolName() const
{
    return tr("清除空白项");
}


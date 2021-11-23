#include "addaffixdialogadapter.h"
#include "addaffixoptionwidget.h"
#include "addaffixotolistmodifyworker.h"

AddAffixDialogAdapter::AddAffixDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(AddAffixOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(AddAffixOptionWidget::staticMetaObject);
}

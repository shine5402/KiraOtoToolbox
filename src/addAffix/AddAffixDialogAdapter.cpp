#include "AddAffixDialogAdapter.h"

#include "AddAffixOptionWidget.h"
#include "AddAffixOtoListModifyWorker.h"

AddAffixDialogAdapter::AddAffixDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(AddAffixOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(AddAffixOptionWidget::staticMetaObject);
}

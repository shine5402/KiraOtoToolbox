#include "RemoveDuplicateDialogAdapter.h"

#include <QMessageBox>

#include "OrganizeDuplicateOtoListModifyWorker.h"
#include "RemoveDuplicateModuleOtoListModifyWorker.h"
#include "RemoveDuplicateOptionWidget.h"
#include "removeAffix/RemoveAffixOtoListModifyWorker.h"
#include "utils/dialogs/ShowOtoListDialog.h"
#include "utils/misc/Misc.h"
#include "utils/models/OtoListShowValueChangeModel.h"

RemoveDuplicateDialogAdapter::RemoveDuplicateDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(RemoveDuplicateModuleOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(RemoveDuplicateOptionWidget::staticMetaObject);
}

void RemoveDuplicateDialogAdapter::replaceUIWidgets(QLayout *rootLayout)
{
    replaceSaveWidget(rootLayout, new OtoFileSaveWidgetWithSecondFileNameAsDeleted(rootLayout->parentWidget()));
    ToolDialogAdapter::replaceUIWidgets(rootLayout);
}

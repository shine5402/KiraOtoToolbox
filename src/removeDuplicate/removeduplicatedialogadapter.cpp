#include "removeduplicatedialogadapter.h"
#include "removeduplicateoptionwidget.h"
#include "utils/models/otolistshowvaluechangemodel.h"
#include "utils/dialogs/showotolistdialog.h"
#include <QMessageBox>
#include "removeAffix/removeaffixotolistmodifyworker.h"
#include "orgnaizeduplicateotolistmodifyworker.h"
#include "removeduplicatemoduleotolistmodifyworker.h"
#include "utils/misc/misc.h"

RemoveDuplicateDialogAdapter::RemoveDuplicateDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(RemoveDuplicateModuleOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(RemoveDuplicateOptionWidget::staticMetaObject);
}

void RemoveDuplicateDialogAdapter::replaceUIWidgets(QLayout* rootLayout)
{
    replaceSaveWidget(rootLayout, new OtoFileSaveWidgetWithSecondFileNameAsDeleted(rootLayout->parentWidget()));
    ToolDialogAdapter::replaceUIWidgets(rootLayout);
}


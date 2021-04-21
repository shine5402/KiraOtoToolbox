#include "overlapbatchsetdialogadapter.h"
#include "overlapbatchsetdialogoptionwidget.h"
#include "utils/models/otolistshowvaluechangemodel.h"
#include "utils/dialogs/showotolistdialog.h"
#include "utils/dialogs/tableviewdialog.h"
#include "overlapbatchsetotolistmodifyworker.h"

OverlapBatchSetDialogAdapter::OverlapBatchSetDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(OverlapBatchSetOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(OverlapBatchSetDialogOptionWidget::staticMetaObject);
}

QString OverlapBatchSetDialogAdapter::getToolName() const
{
    return tr("批量修改Overlap");
}

#include "convertplusminusrightdialogadapter.h"
#include "convertplusminusrightoptionwidget.h"
#include "convertplusminusrightotolistmodifyworker.h"
#include <QMessageBox>

ConvertPlusMinusRightDialogAdapter::ConvertPlusMinusRightDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(ConvertPlusMinusRightOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(ConvertPlusMinusRightOptionWidget::staticMetaObject);
}

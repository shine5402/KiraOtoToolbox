#include "ConvertPlusMinusRightDialogAdapter.h"
#include "ConvertPlusMinusRightOptionWidget.h"
#include "ConvertPlusMinusRightOtoListModifyWorker.h"
#include <QMessageBox>

ConvertPlusMinusRightDialogAdapter::ConvertPlusMinusRightDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(ConvertPlusMinusRightOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(ConvertPlusMinusRightOptionWidget::staticMetaObject);
}

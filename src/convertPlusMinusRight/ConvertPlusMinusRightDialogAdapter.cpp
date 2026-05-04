#include "ConvertPlusMinusRightDialogAdapter.h"

#include <QMessageBox>

#include "ConvertPlusMinusRightOptionWidget.h"
#include "ConvertPlusMinusRightOtoListModifyWorker.h"

ConvertPlusMinusRightDialogAdapter::ConvertPlusMinusRightDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(ConvertPlusMinusRightOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(ConvertPlusMinusRightOptionWidget::staticMetaObject);
}

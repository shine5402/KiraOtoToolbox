#include "chaindialogadapter.h"
#include "chainotolistmodifyworker.h"
#include "chaintooloptionwidget.h"

ChainDialogAdapter::ChainDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorker(new ChainOtoListModifyWorker(this));
    setOptionWidget(new ChainToolOptionWidget);
}

QString ChainDialogAdapter::getWindowTitle() const
{
    return tr("进行多个操作");
}

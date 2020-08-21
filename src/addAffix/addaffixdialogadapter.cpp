#include "addaffixdialogadapter.h"
#include "addaffixoptionwidget.h"
#include "addaffixotolistmodifyworker.h"

AddAffixDialogAdapter::AddAffixDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{

}

void AddAffixDialogAdapter::setupSpecificUIWidgets(QLayout* rootLayout)
{
    replaceOptionWidget(rootLayout, new AddAffixOptionWidget(rootLayout->parentWidget()));
}

bool AddAffixDialogAdapter::doWorkAdapter(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* options, QWidget* dialogParent)
{
    AddAffixOtoListModifyWorker worker;
    if (worker.doWork(srcOtoList, resultOtoList, secondSaveOtoList, options))
        return askUserForApplyChanges(srcOtoList, resultOtoList, ValueChangeModel, tr("确认前/后缀增加"), tr("点击“确定”来确认此修改，点击“取消”以取消本次操作。"), dialogParent);
    return false;
}

QString AddAffixDialogAdapter::getWindowTitle() const
{
    return tr("添加前/后缀");
}

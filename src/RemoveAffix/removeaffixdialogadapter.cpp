#include "removeaffixdialogadapter.h"
#include "removeaffixoptionwidget.h"
#include "removeaffixotolistmodifyworker.h"

RemoveAffixDialogAdapter::RemoveAffixDialogAdapter(QWidget* parent) : ToolDialogAdapter(parent)
{

}

void RemoveAffixDialogAdapter::setupSpecificUIWidgets(QLayout* rootLayout)
{
    replaceOptionWidget(rootLayout, new RemoveAffixOptionWidget(rootLayout->parentWidget()));
}

bool RemoveAffixDialogAdapter::doWorkAdapter(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* options, QWidget* dialogParent)
{
    //TODO:转移到下层提供默认实现
    RemoveAffixOtoListModifyWorker worker;
    if (worker.doWork(srcOtoList, resultOtoList, secondSaveOtoList, options)){
        return askUserForApplyChanges(srcOtoList, resultOtoList, ValueChangeModel, tr("确认前/后缀移除"),tr("点击“确定”来确认此修改，点击“取消”以取消本次操作。"), dialogParent);
    }
    return false;
}

QString RemoveAffixDialogAdapter::getWindowTitle() const
{
    return tr("去除别名前/后缀");
}


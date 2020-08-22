#include "removeduplicatedialogadapter.h"
#include "removeduplicatedialogoptionwidget.h"
#include "utils/models/otolistshowvaluechangemodel.h"
#include "utils/dialogs/showotolistdialog.h"
#include "utils/dialogs/tableviewdialog.h"
#include <QMessageBox>
#ifdef SHINE5402OTOBOX_TEST
#include <QTimer>
#endif
#include "removeAffix/removeaffixotolistmodifyworker.h"
#include "orgnaizeduplicateotolistmodifyworker.h"
#include "removeduplicateotolistmodifyworker.h"

RemoveDuplicateDialogAdapter::RemoveDuplicateDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{

}

void RemoveDuplicateDialogAdapter::setupSpecificUIWidgets(QLayout* rootLayout)
{
    replaceOptionWidget(rootLayout, new RemoveDuplicateDialogOptionWidget(rootLayout->parentWidget()));
    replaceSaveWidget(rootLayout, new OtoFileSaveWidgetWithSecondFileNameAsDeleted(rootLayout->parentWidget()));
}

bool RemoveDuplicateDialogAdapter::doWorkAdapter(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                                 OtoEntryList& secondSaveOtoList, const ToolOptions& options,
                                                 QWidget* dialogParent)
{
    //TODO:使用循环
    OtoEntryList lastResult = srcOtoList;
    OtoEntryList currentResult;
    bool success = false;

    auto updateResult = [&](){
        lastResult = std::move(currentResult);
        currentResult = {};
    };

    RemoveAffixOtoListModifyWorker removeAffixWorker;
    success |= removeAffixWorker.doWork(lastResult, currentResult, secondSaveOtoList, options.extract("affixRemove"));
    updateResult();

    if (options.getOption("shouldOrganize").toBool()){
        OrgnaizeDuplicateOtoListModifyWorker orgnaizeWorker;
        success |= orgnaizeWorker.doWork(lastResult, currentResult, secondSaveOtoList, options);
        auto apply = askUserForApplyChanges(srcOtoList, currentResult, ValueChangeModel, tr("重复项整理结果"), tr("以下特别标出的原音设定的别名将会被重命名，其中多余的重复项将根据您的设置在下一步被删除。点击“确定”来确认此修改，点击“取消”以取消本次操作。"), dialogParent);
        if (!apply)
            return false;
        updateResult();
    }

    RemoveDuplicateOtoListModifyWorker removeDuplicateWorker;
    success |= removeDuplicateWorker.doWork(lastResult, currentResult, secondSaveOtoList, options);

    auto shouldDelete = askUserForSecondSave(secondSaveOtoList, tr("要被删除的原音设定条目列表"), tr("以下 %1 条原音设定条目将会被删除，或是被保存到您指定的文件中。点击“确定”来确认此修改，点击“取消”以取消本次操作。").arg(secondSaveOtoList.count()), dialogParent);
    if (shouldDelete == QDialog::Rejected)
        return false;

    resultOtoList = currentResult;
    return success;
}

QString RemoveDuplicateDialogAdapter::getWindowTitle() const
{
    return tr("去除重复项");
}

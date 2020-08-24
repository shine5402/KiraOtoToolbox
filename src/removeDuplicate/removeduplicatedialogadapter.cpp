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
#include "removeduplicatemoduleotolistmodifyworker.h"

RemoveDuplicateDialogAdapter::RemoveDuplicateDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorker(new RemoveDuplicateModuleOtoListModifyWorker(this));
    setOptionWidget(new RemoveDuplicateDialogOptionWidget);
}

void RemoveDuplicateDialogAdapter::setupSpecificUIWidgets(QLayout* rootLayout)
{
    replaceSaveWidget(rootLayout, new OtoFileSaveWidgetWithSecondFileNameAsDeleted(rootLayout->parentWidget()));
    ToolDialogAdapter::setupSpecificUIWidgets(rootLayout);
}

bool RemoveDuplicateDialogAdapter::doWorkAdapter(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions& options, QWidget* dialogParent)
{
    if (getWorker()->doWork(srcOtoList, resultOtoList, secondSaveOtoList, options))
    {
        auto specificWorker = static_cast<RemoveDuplicateModuleOtoListModifyWorker*>(getWorker());
        if ((!specificWorker->getOrganizeResult().isEmpty()) &&
                (!askUserForApplyChanges(srcOtoList, specificWorker->getOrganizeResult(),
                                         ValueChangeModel, tr("重复项整理结果"),
                                         tr("以下特别标出的原音设定的别名将会被重命名，其中多余的重复项将根据您的设置在下一步被删除。点击“确定”来确认此修改，点击“取消”以取消本次操作。"),
                                         dialogParent)))
            return false;
        if ((!secondSaveOtoList.isEmpty()) && (!askUserForSecondSave(secondSaveOtoList, tr("要被删除的原音设定条目列表"),
                                                                     tr("以下 %1 条原音设定条目将会被删除，或是被保存到您指定的文件中。点击“确定”来确认此修改，点击“取消”以取消本次操作。").arg(secondSaveOtoList.count()),
                                                                     dialogParent)))
            return false;
        return askUserForApplyChanges(srcOtoList, resultOtoList, Diff,
                                      tr("确认更改"),
                                      tr("以下显示了根据您的要求要对原音设定数据执行的修改。点击“确定”来确认此修改，点击“取消”以取消本次操作。"),
                                      dialogParent);
    }
    return false;
}

QString RemoveDuplicateDialogAdapter::getWindowTitle() const
{
    return tr("去除重复项");
}

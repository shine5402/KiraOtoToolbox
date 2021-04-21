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
#include "utils/misc/misc.h"

RemoveDuplicateDialogAdapter::RemoveDuplicateDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(RemoveDuplicateModuleOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(RemoveDuplicateDialogOptionWidget::staticMetaObject);
}

void RemoveDuplicateDialogAdapter::replaceUIWidgets(QLayout* rootLayout)
{
    replaceSaveWidget(rootLayout, new OtoFileSaveWidgetWithSecondFileNameAsDeleted(rootLayout->parentWidget()));
    ToolDialogAdapter::replaceUIWidgets(rootLayout);
}

bool RemoveDuplicateDialogAdapter::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options, QWidget* dialogParent)
{
    auto precision = options.getOption("save/precision").toInt();
    if (ToolDialogAdapter::doWork(srcOtoList, resultOtoList, secondSaveOtoList, options))
    {
        auto specificWorker = new RemoveDuplicateModuleOtoListModifyWorker(this);
        if ((!specificWorker->getOrganizeResult().isEmpty()) &&
                (!Misc::showOtoDiffDialog(srcOtoList, specificWorker->getOrganizeResult(), precision, tr("重复项整理结果"),
                                         tr("以下特别标出的原音设定的别名将会被重命名，其中多余的重复项将根据您的设置在下一步被删除。点击“确定”来确认此修改，点击“取消”以取消本次操作。"),
                                         dialogParent,
                                         Misc::ValueChangeModel)))
            return false;
        if ((!secondSaveOtoList.isEmpty()) && (!Misc::askUserWithShowOtoList(secondSaveOtoList, tr("要被删除的原音设定条目列表"),
                                                                     tr("以下 %1 条原音设定条目将会被删除，或是被保存到您指定的文件中。点击“确定”来确认此修改，点击“取消”以取消本次操作。").arg(secondSaveOtoList.count()),
                                                                     dialogParent)))
            return false;
        return Misc::showOtoDiffDialog(srcOtoList, resultOtoList, precision,
                                      tr("确认更改"),
                                      tr("以下显示了根据您的要求要对原音设定数据执行的修改。点击“确定”来确认此修改，点击“取消”以取消本次操作。"),
                                      dialogParent,
                                       Misc::Diff);
    }
    return false;
}

QString RemoveDuplicateDialogAdapter::getToolName() const
{
    return tr("去除重复项");
}

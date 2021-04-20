#include "tooldialogadapter.h"
#include <QWidget>
#include <QMessageBox>
#include <QSaveFile>
#include <QTextStream>
#include <utils/dialogs/showdiffdialog.h>
#include <utils/models/otolistshowvaluechangemodel.h>
#include <utils/dialogs/tableviewdialog.h>
#include <QTimer>
#include <utils/dialogs/showotolistdialog.h>
#include "utils/misc/misc.h"


ToolDialogAdapter::ToolDialogAdapter(QObject *parent) : QObject(parent)
{

}

void ToolDialogAdapter::replaceUIWidgets(QLayout* rootLayout)
{
    Q_ASSERT_X(optionWidget, "setupSpecificUIWidgets", "OptionWidget is not set.");
    optionWidget->setOptions({});
    optionWidget->setParent(rootLayout->parentWidget());
    replaceOptionWidget(rootLayout, optionWidget);
}

bool ToolDialogAdapter::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options, QWidget* dialogParent)
{
    Q_ASSERT_X(getWorker(), "doWorkAdapter", "Worker is not set.");
    auto precision = options.getOption("save/precision").toInt();
    if (doWork(srcOtoList, resultOtoList, secondSaveOtoList, options))
        return Misc::showOtoDiffDialog(srcOtoList, resultOtoList, precision,
                                      tr("确认更改"),
                                      tr("以下显示了根据您的要求要对原音设定数据执行的修改。点击“确定”来确认此修改，点击“取消”以取消本次操作。"),
                                      dialogParent);
    return false;
}

bool ToolDialogAdapter::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_ASSERT_X(getWorker(), "doWorkAdapter", "Worker is not set.");
    return getWorker()->doWork(srcOtoList, resultOtoList, secondSaveOtoList, options);
}

QString ToolDialogAdapter::getToolName() const
{
    return metaObject()->className();
}

void ToolDialogAdapter::setOptionWidget(ToolOptionWidget* value)
{
    optionWidget = value;
}

OtoListModifyWorker* ToolDialogAdapter::getWorker() const
{
    return worker;
}

void ToolDialogAdapter::setWorker(OtoListModifyWorker* value)
{
    worker = value;
}

void ToolDialogAdapter::replaceOptionWidget(QLayout* rootLayout, ToolOptionWidget* newOptionWidget)
{
    if (optionWidget != newOptionWidget)
        optionWidget = newOptionWidget;
    auto optionLayout = rootLayout->parentWidget()->findChild<QLayout*>("optionLayout");
    Misc::replaceWidget(optionLayout, "optionWidget", newOptionWidget, rootLayout->parentWidget());
}

void ToolDialogAdapter::replaceSaveWidget(QLayout* rootLayout, OtoFileSaveWidget* newSaveWidget)
{
    auto saveWidgetRootLayout = rootLayout->parentWidget()->findChild<QWidget *>("stackedSaveWidget")->findChild<QWidget *>("singleSave")->layout();
    Misc::replaceWidget(saveWidgetRootLayout, "otoSaveWidget", newSaveWidget);
}


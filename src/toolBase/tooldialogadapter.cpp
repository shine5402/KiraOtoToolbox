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
#include "presetwidgetcontainer.h"


ToolDialogAdapter::ToolDialogAdapter(QObject *parent) : QObject(parent)
{

}

void ToolDialogAdapter::replaceUIWidgets(QLayout* rootLayout)
{
    Q_ASSERT_X(optionWidgetMetaObj.inherits(&ToolOptionWidget::staticMetaObject), "setupSpecificUIWidgets", "OptionWidget is not set.");
    auto presetWidgetContainer = new PresetWidgetContainer(optionWidgetMetaObj, rootLayout->parentWidget());
    auto optionLayout = rootLayout->parentWidget()->findChild<QLayout*>("optionLayout");
    Misc::replaceWidget(optionLayout, "presetWidgetContainer", presetWidgetContainer, rootLayout->parentWidget());
}

//Though we can use other approach to prevent the need of dialogParent, we use this overrload to indicate that it will raise a dialog, leaving the other overload reflecting a quiet process.
bool ToolDialogAdapter::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options, QWidget* dialogParent)
{
    auto precision = options.getOption("save/precision").toInt();
    if (doWork(srcOtoList, resultOtoList, secondSaveOtoList, options))
        return Misc::showOtoDiffDialog(srcOtoList, resultOtoList, precision,
                                      tr("Confirm changes"),
                                      tr("These are changes that will be applied to oto data. Click \"OK\" to confirm, \"Cancel\" to discard these changes."),
                                      dialogParent);
    else
        QMessageBox::critical(dialogParent, {}, tr("Error occured while processing. Please check and try again."));
    return false;
}

bool ToolDialogAdapter::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_ASSERT_X(workerMetaObj.inherits(&OtoListModifyWorker::staticMetaObject), "doWorkAdapter", "Worker is not set.");
    auto worker = qobject_cast<OtoListModifyWorker *>(workerMetaObj.newInstance(Q_ARG(QObject*, this)));
    return worker->doWork(srcOtoList, resultOtoList, secondSaveOtoList, options);
}

QString ToolDialogAdapter::getToolName() const
{
    Q_UNREACHABLE();
    return {};
}

std::unique_ptr<OtoListModifyWorker> ToolDialogAdapter::getWorkerInstance() const
{
    return std::unique_ptr<OtoListModifyWorker>(qobject_cast<OtoListModifyWorker*>(workerMetaObj.newInstance()));
}

void ToolDialogAdapter::setWorkerMetaObj(const QMetaObject& value)
{
    workerMetaObj = value;
}

QMetaObject ToolDialogAdapter::getWorkerMetaObj() const
{
    return workerMetaObj;
}

QMetaObject ToolDialogAdapter::getOptionWidgetMetaObj() const
{
    return optionWidgetMetaObj;
}

void ToolDialogAdapter::setOptionWidgetMetaObj(const QMetaObject& value)
{
    optionWidgetMetaObj = value;
}

void ToolDialogAdapter::replaceSaveWidget(QLayout* rootLayout, OtoFileSaveWidget* newSaveWidget)
{
    auto saveWidgetRootLayout = rootLayout->parentWidget()->findChild<QWidget *>("stackedSaveWidget")->findChild<QWidget *>("singleSave")->layout();
    Misc::replaceWidget(saveWidgetRootLayout, "otoSaveWidget", newSaveWidget);
}


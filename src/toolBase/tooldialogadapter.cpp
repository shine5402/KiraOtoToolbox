#include "tooldialogadapter.h"
#include <QWidget>
#include <QMessageBox>
#include <QSaveFile>
#include <QTextStream>
#include <kira/dialogs/showdiffdialog.h>
#include <utils/models/otolistshowvaluechangemodel.h>
#include <kira/dialogs/tableviewdialog.h>
#include <QTimer>
#include <utils/dialogs/showotolistdialog.h>
#include "utils/misc/misc.h"
#include <kira/widgets/misc.h>
#include "presetwidgetcontainer.h"


ToolDialogAdapter::ToolDialogAdapter(QObject *parent) : QObject(parent)
{

}

void ToolDialogAdapter::replaceUIWidgets(QLayout* rootLayout)
{
    Q_ASSERT_X(optionWidgetMetaObj.inherits(&ToolOptionWidget::staticMetaObject), "setupSpecificUIWidgets", "OptionWidget is not set.");
    auto presetWidgetContainer = new PresetWidgetContainer(optionWidgetMetaObj, rootLayout->parentWidget());
    auto optionLayout = rootLayout->parentWidget()->findChild<QLayout*>("optionLayout");
    replaceWidget(optionLayout, "presetWidgetContainer", presetWidgetContainer, rootLayout->parentWidget());
}

bool ToolDialogAdapter::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options, QWidget* dialogParent)
{
    auto precision = options.getOption("save/precision").toInt();
    try {
        getWorkerInstance()->doWork(srcOtoList, resultOtoList, secondSaveOtoList, options);
        return Misc::showOtoDiffDialog(srcOtoList, resultOtoList, precision,
                                       tr("Confirm changes"),
                                       tr("These are changes that will be applied to oto data. Click \"OK\" to confirm, \"Cancel\" to discard these changes."),
                                       dialogParent);
    }
    catch (const ToolException& e){
        QMessageBox msgBox(dialogParent);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(tr("Error occured while processing. Please check and try again."));
        msgBox.setInformativeText(e.info());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return false;
    }
    catch (const std::exception& e){
        QMessageBox msgBox(dialogParent);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(tr("Error occured while processing. Please check and try again."));
        msgBox.setInformativeText(e.what());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return false;
    }
    catch (...){
        QMessageBox::critical(dialogParent, {}, tr("Error occured while processing. Please check and try again."));
        return false;
    }

    return false;
}

QString ToolDialogAdapter::getToolName() const
{
    qFatal("DEFINE_TOOL_NAME() not used in tool dialog adapter.");
    Q_UNREACHABLE();
    return {};
}

std::unique_ptr<OtoListModifyWorker> ToolDialogAdapter::getWorkerInstance() const
{
    Q_ASSERT_X(workerMetaObj.inherits(&OtoListModifyWorker::staticMetaObject), "doWorkAdapter", "Worker is not set.");
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
    replaceWidget(saveWidgetRootLayout, "otoSaveWidget", newSaveWidget);
}


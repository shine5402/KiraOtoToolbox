#include "ToolDialogAdapter.h"

#include <QMessageBox>
#include <QSaveFile>
#include <QTextStream>
#include <QTimer>
#include <QWidget>

#include "PresetWidgetContainer.h"
#include "utils/dialogs/ShowDiffDialog.h"
#include "utils/dialogs/ShowOtoListDialog.h"
#include "utils/dialogs/TableViewDialog.h"
#include "utils/misc/Misc.h"
#include "utils/models/OtoListShowValueChangeModel.h"
#include "utils/widgets/Misc.h"

ToolDialogAdapter::ToolDialogAdapter(QObject *parent) : QObject(parent)
{
}

void ToolDialogAdapter::replaceUIWidgets(QLayout *rootLayout)
{
    Q_ASSERT_X(optionWidgetMetaObj.inherits(&ToolOptionWidget::staticMetaObject), "setupSpecificUIWidgets",
               "OptionWidget is not set.");
    auto presetWidgetContainer = new PresetWidgetContainer(optionWidgetMetaObj, rootLayout->parentWidget());
    auto optionLayout = rootLayout->parentWidget()->findChild<QLayout *>("optionLayout");
    replaceWidget(optionLayout, "presetWidgetContainer", presetWidgetContainer, rootLayout->parentWidget());
}

bool ToolDialogAdapter::doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                               OtoEntryList &secondSaveOtoList, const OptionContainer &options, QWidget *dialogParent)
{
    auto precision = options.getOption("save/precision").toInt();
    try {
        auto worker = getWorkerInstance();
        if (!worker) {
            QMessageBox::critical(dialogParent, {},
                                  tr("Failed to initialize tool worker. Please report this bug."));
            return false;
        }
        worker->doWork(srcOtoList, resultOtoList, secondSaveOtoList, options);
        if (worker->needConfirm()) {
            auto msgs = worker->getConfirmMsgs();
            for (const auto &msg : qAsConst(msgs)) {
                auto result = msg.userDialog()->exec();
                if (!worker->isConfirmDialogAccepted(msg.typeId(), result))
                    return false;
            }
        }
        auto result = Misc::showOtoDiffDialog(srcOtoList, resultOtoList, precision, tr("Confirm changes"),
                                              tr("These are changes that will be applied to oto data. Click \"OK\" to "
                                                 "confirm, \"Cancel\" to discard these changes."),
                                              dialogParent);
        if (result && worker->needConfirm())
            worker->commit();

        return result;
    } catch (const ToolException &e) {
        QMessageBox msgBox(dialogParent);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(tr("Error occured while processing. Please check and try again."));
        msgBox.setInformativeText(e.info());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return false;
    } catch (const std::exception &e) {
        QMessageBox msgBox(dialogParent);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(tr("Error occured while processing. Please check and try again."));
        msgBox.setInformativeText(e.what());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return false;
    } catch (...) {
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
    if (!workerMetaObj.inherits(&OtoListModifyWorker::staticMetaObject)) {
        qCritical() << "Worker meta object is not properly set. Tool cannot be executed.";
        return nullptr;
    }
    return std::unique_ptr<OtoListModifyWorker>(
        qobject_cast<OtoListModifyWorker *>(workerMetaObj.newInstance()));
}

void ToolDialogAdapter::setWorkerMetaObj(const QMetaObject &value)
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

void ToolDialogAdapter::setOptionWidgetMetaObj(const QMetaObject &value)
{
    optionWidgetMetaObj = value;
}

void ToolDialogAdapter::replaceSaveWidget(QLayout *rootLayout, OtoFileSaveWidget *newSaveWidget)
{
    auto saveWidgetRootLayout = rootLayout->parentWidget()
                                    ->findChild<QWidget *>("stackedSaveWidget")
                                    ->findChild<QWidget *>("singleSave")
                                    ->layout();
    replaceWidget(saveWidgetRootLayout, "otoSaveWidget", newSaveWidget);
}

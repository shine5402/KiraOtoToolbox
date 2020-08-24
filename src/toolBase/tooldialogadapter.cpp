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


ToolDialogAdapter::ToolDialogAdapter(QObject *parent) : QObject(parent)
{

}

void ToolDialogAdapter::setupSpecificUIWidgets(QLayout* rootLayout)
{
    Q_ASSERT_X(optionWidget, "setupSpecificUIWidgets", "OptionWidget is not set.");
    optionWidget->setParent(rootLayout->parentWidget());
    replaceOptionWidget(rootLayout, optionWidget);
}

bool ToolDialogAdapter::doWork(const OtoFileLoadWidget* loadWidget, const OtoFileSaveWidget* saveWidget, const ToolOptionWidget* optionWidget, QWidget* dialogParent)
{
    const auto entryList = loadWidget->getEntryList();
    OtoEntryList entryListWorking{};
    OtoEntryList secondSaveList{};
    auto options = optionWidget->getOptions();

    auto saveOtoFile = [&](const OtoEntryList& entryList, const QString& fileName, const QString& usage) -> bool{
        QString errorString;
        auto result = OtoEntryFunctions::writeOtoListToFile(fileName, entryList, nullptr, &errorString);
        if (!result)
        {
#ifdef SHINE5402OTOBOX_TEST
            Q_ASSERT(false);
#endif
            QMessageBox::critical(dialogParent, tr("保存失败"), [&]() -> QString{
                                      QString result;
                                      QTextStream stream(&result);
                                      stream << tr("在保存 %1 时发生错误。").arg(fileName);
                                      if (!usage.isEmpty())
                                      stream << tr("该文件的用途是 %1。").arg(usage);
                                      stream << tr("遇到的错误是：%1").arg(errorString);
                                      return result;
                                  }());
        }
        return result;
    };

    auto result = doWorkAdapter(entryList, entryListWorking, secondSaveList, options, dialogParent);
    if (result)
    {
        if (saveWidget->isSecondFileNameAvailable() && saveWidget->isSecondFileNameUsed()){
            result = saveOtoFile(secondSaveList, saveWidget->secondFileName(), saveWidget->secondFileNameUsage());
            if (!result)
                return false;
        }
        result = saveOtoFile(entryListWorking, saveWidget->isSaveToSrc() ? loadWidget->fileName() : saveWidget->fileName(), tr("保存处理结果"));
    }
    return result;
}

bool ToolDialogAdapter::doWorkAdapter(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions& options, QWidget* dialogParent)
{
    Q_ASSERT_X(getWorker(), "doWorkAdapter", "Worker is not set.");
    if (getWorker()->doWork(srcOtoList, resultOtoList, secondSaveOtoList, options))
        return askUserForApplyChanges(srcOtoList, resultOtoList,
                                      srcOtoList.count() == resultOtoList.count() ? ValueChangeModel : Diff,
                                      tr("确认更改"),
                                      tr("以下显示了根据您的要求要对原音设定数据执行的修改。点击“确定”来确认此修改，点击“取消”以取消本次操作。"),
                                      dialogParent);
    return false;
}

void ToolDialogAdapter::replaceWidget(QLayout* parentLayout, const QString& widgetName, QWidget* newWidget, QWidget* newParent){
    auto oldWidget = parentLayout->parentWidget()->findChild<QWidget*>(widgetName);
    if (oldWidget){
        newWidget->setParent(newParent ? newParent : parentLayout->parentWidget());
        auto previousWidget = parentLayout->replaceWidget(oldWidget, newWidget);
        if (previousWidget){
            oldWidget->deleteLater();
            delete previousWidget;
        }
    }
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
    replaceWidget(optionLayout, "optionWidget", newOptionWidget, rootLayout->parentWidget());
}

void ToolDialogAdapter::replaceSaveWidget(QLayout* rootLayout, OtoFileSaveWidget* newSaveWidget)
{
    replaceWidget(rootLayout, "otoSaveWidget", newSaveWidget);
}

bool ToolDialogAdapter::askUserForApplyChanges(const OtoEntryList& srcOtoList, const OtoEntryList& resultOtoList, ToolDialogAdapter::ChangeAskDialogType changeAskDialogType,
                                               const QString& title, const QString& label, QWidget* dialogParent)
{
    auto dialog = [&]() -> QDialog* {

            switch (changeAskDialogType) {
            case (ValueChangeModel):{
            auto model = new OtoListShowValueChangeModel(&srcOtoList, &resultOtoList, dialogParent);
            return new TableViewDialog(dialogParent, model, title, label, QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
}
            case (Diff):{
            auto otoList2String = [](const OtoEntryList& list) -> QString{
        QStringList stringList{};
        for (auto i : list){
            stringList.append(i.toString());
        }
        return stringList.join("\n");
    };
            return new ShowDiffDialog(otoList2String(srcOtoList), otoList2String(resultOtoList), title, label, QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialogParent);
}
}
            return nullptr;
}();
#ifdef SHINE5402OTOBOX_TEST
    QTimer::singleShot(0, dialog, &QDialog::accept);
#endif
    return dialog->exec();
}

bool ToolDialogAdapter::askUserForSecondSave(const OtoEntryList& secondSaveData, const QString& title, const QString& label, QWidget* dialogParent)
{
    auto dialog = new ShowOtoListDialog(&secondSaveData, dialogParent);
    dialog->setLabel(label);
    dialog->setWindowTitle(title);
    dialog->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
#ifdef SHINE5402OTOBOX_TEST
    QTimer::singleShot(0, dialog, &QDialog::accept);
#endif
    return dialog->exec();
}


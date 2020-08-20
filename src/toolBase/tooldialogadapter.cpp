#include "tooldialogadapter.h"
#include <QWidget>
#include <QMessageBox>
#include <QSaveFile>
#include <QTextStream>


ToolDialogAdapter::ToolDialogAdapter(QObject *parent) : QObject(parent)
{

}

bool ToolDialogAdapter::doWork(const OtoFileLoadWidget* loadWidget, const OtoFileSaveWidget* saveWidget, const ToolOptionWidget* optionWidget, QWidget* dialogParent)
{
    const auto entryList = loadWidget->getEntryList();
    auto entryListWorking = entryList;
    OtoEntryList secondSaveList{};
    auto options = optionWidget->getOptions(this);

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

void ToolDialogAdapter::replaceWidget(QLayout* parentLayout, const QString& widgetName, QWidget* newWidget, QWidget* newParent){
    auto oldWidget = parentLayout->parentWidget()->findChild<QWidget*>(widgetName);
    if (oldWidget){
        newWidget->setParent(newParent ? newParent : parentLayout->parentWidget());
        auto previousOptionWidget = parentLayout->replaceWidget(oldWidget, newWidget);
        if (previousOptionWidget)
            previousOptionWidget->widget()->deleteLater();
    }
}

void ToolDialogAdapter::replaceOptionWidget(QLayout* rootLayout, ToolOptionWidget* newOptionWidget)
{
    auto optionLayout = rootLayout->parentWidget()->findChild<QLayout*>("optionLayout");
    replaceWidget(optionLayout, "optionWidget", newOptionWidget, rootLayout->parentWidget());
}

void ToolDialogAdapter::replaceSaveWidget(QLayout* rootLayout, OtoFileSaveWidget* newSaveWidget)
{
    replaceWidget(rootLayout, "otoSaveWidget", newSaveWidget);
}

bool ToolDialogAdapter::askUserForApplyChanges(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, ToolDialogAdapter::ChangeAskDialogType changeAskDialogType, OtoEntryList& secondSaveOtoList,
                                               const QString& title, const QString& label, QWidget* dialogParent)
{
    //TODO:建立增删的Model
}


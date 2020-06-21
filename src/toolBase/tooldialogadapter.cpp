#include "tooldialogadapter.h"
#include <QWidget>


ToolDialogAdapter::ToolDialogAdapter(QObject *parent) : QObject(parent)
{

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


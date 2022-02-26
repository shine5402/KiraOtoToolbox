#include <kira/widgets/misc.h>
#include <QWidget>
#include <QLayout>
#include <QStackedWidget>

void replaceWidget(QLayout* parentLayout, const QString& widgetName, QWidget* newWidget, QWidget* newParent)
{
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

void refreshStackedWidgetSize(QStackedWidget* stackedWidget)
{
    for (int i = 0; i < stackedWidget->count(); i++){
        auto currentWidget = stackedWidget->widget(i);
        auto sizePolicy = currentWidget->sizePolicy();
        if (i != stackedWidget->currentIndex())
        {
            sizePolicy.setVerticalPolicy(QSizePolicy::Ignored);
        }
        else{
            sizePolicy.setVerticalPolicy(QSizePolicy::Preferred);
        }
        stackedWidget->widget(i)->setSizePolicy(sizePolicy);
    }
    stackedWidget->adjustSize();
}

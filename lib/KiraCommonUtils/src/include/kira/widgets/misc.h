#ifndef KIRA_WIDGETS_MISC_H
#define KIRA_WIDGETS_MISC_H

class QLayout;
class QWidget;
class QStackedWidget;
#include <QString>

void replaceWidget(QLayout* parentLayout, const QString& widgetName,
                   QWidget* newWidget, QWidget* newParent = nullptr);

void refreshStackedWidgetSize(QStackedWidget* stackedWidget);
                   
#endif // KIRA_WIDGETS_MISC_H

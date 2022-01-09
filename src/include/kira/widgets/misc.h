#ifndef MISC_H
#define MISC_H

class QLayout;
class QWidget;
class QStackedWidget;
#include <QString>

void replaceWidget(QLayout* parentLayout, const QString& widgetName,
                   QWidget* newWidget, QWidget* newParent = nullptr);

void refreshStackedWidgetSize(QStackedWidget* stackedWidget);
                   
#endif // MISC_H

#include "tooloptionwidget.h"

ToolOptionWidget::ToolOptionWidget(QWidget *parent) : QWidget(parent)
{
}

ToolOptions* ToolOptionWidget::getOptions(QObject*) const
{
    return nullptr;
}

void ToolOptionWidget::setOptions(const ToolOptions*)
{

}

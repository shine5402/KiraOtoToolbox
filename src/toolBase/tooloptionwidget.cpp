#include "tooloptionwidget.h"
#include <QVBoxLayout>
#include <QLabel>

ToolOptionWidget::ToolOptionWidget(QWidget *parent) : QWidget(parent)
{

}

EmptyToolOptionWidget::EmptyToolOptionWidget(QWidget* parent) : ToolOptionWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    setLayout(layout);
    auto label = new QLabel(tr("该操作没有配置项。"), this);
    layout->addStretch(1);
    layout->addWidget(label);
    layout->addStretch(1);
}

OptionContainer EmptyToolOptionWidget::getOptions() const
{
    return OptionContainer{};
}

void EmptyToolOptionWidget::setOptions(const OptionContainer& options)
{
    Q_UNUSED(options)
}

#include "notdoanythingoptionwidget.h"
#include <QVBoxLayout>
#include <QLabel>

NotDoAnythingOptionWidget::NotDoAnythingOptionWidget(QWidget *parent) : ToolOptionWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    setLayout(layout);
    auto label = new QLabel(tr("该操作没有配置项。\n"
"请注意，本工具直接输出输入的源数据（即“什么都不做”），但是你可以使用本工具来控制保存选项。"), this);
    layout->addStretch(1);
    layout->addWidget(label);
    layout->addStretch(1);
}

OptionContainer NotDoAnythingOptionWidget::getOptions() const
{
    return {};
}

void NotDoAnythingOptionWidget::setOptions(const OptionContainer& options)
{
    Q_UNUSED(options);
}

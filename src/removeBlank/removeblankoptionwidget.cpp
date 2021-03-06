#include "removeblankoptionwidget.h"

#include <QCheckBox>
#include <QVBoxLayout>

RemoveBlankOptionWidget::RemoveBlankOptionWidget(QWidget* parent) : ToolOptionWidget(parent)
{
    ignoreRightCheckBox = new QCheckBox(tr("忽略负的右值"), this);
    ignoreRightCheckBox->setToolTip(tr("当除了右之外的数值为0时，而右为负值时，将这条原音设定条目视为空。"));
    ignoreRightCheckBox->setCheckable(true);
    ignoreRightCheckBox->setChecked(false);

    auto layout = new QVBoxLayout(this);

    layout->addWidget(ignoreRightCheckBox);
    layout->addStretch();
}

OptionContainer RemoveBlankOptionWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("ignoreRight", ignoreRightCheckBox->isChecked());
    return options;
}

void RemoveBlankOptionWidget::setOptions(const OptionContainer& options)
{
    ignoreRightCheckBox->setChecked(options.getOption("ignoreRight").toBool());
}

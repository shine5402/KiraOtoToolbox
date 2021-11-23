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

    connect(ignoreRightCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
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


QJsonObject RemoveBlankOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject jsonObj;
    jsonObj.insert("ignoreRight", options.getOption("ignoreRight").toBool());
    return jsonObj;
}

OptionContainer RemoveBlankOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;
    options.setOption("ignoreRight", json.value("ignoreRight").toBool());
    return options;
}

int RemoveBlankOptionWidget::optionJsonVersion() const
{
    return 1;
}

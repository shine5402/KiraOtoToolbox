#include "removeblankoptionwidget.h"

#include <QCheckBox>
#include <QVBoxLayout>

RemoveBlankOptionWidget::RemoveBlankOptionWidget(QWidget* parent) : ToolOptionWidget(parent)
{
    ignoreRightCheckBox = new QCheckBox(tr("Ignore negative right value"), this);
    ignoreRightCheckBox->setToolTip(tr("When all value other than right beging 0, see this oto entry as empty."));
    ignoreRightCheckBox->setCheckable(true);
    ignoreRightCheckBox->setChecked(false);

    auto layout = new QVBoxLayout(this);

    layout->setContentsMargins(0,0,0,0);
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

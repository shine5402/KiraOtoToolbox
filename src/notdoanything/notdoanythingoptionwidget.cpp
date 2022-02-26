#include "notdoanythingoptionwidget.h"
#include <QVBoxLayout>
#include <QLabel>

NotDoAnythingOptionWidget::NotDoAnythingOptionWidget(QWidget *parent) : ToolOptionWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    setLayout(layout);
    auto label = new QLabel(tr("There is nothing to configure.\n"
"ATTENTION: This tool will simply forward the input to output (a.k.a. do nothing), "
"but you can adjust save options with this tool."), this);
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

QJsonObject NotDoAnythingOptionWidget::optionsToJson(const OptionContainer& options) const
{
    Q_UNUSED(options)
    return {};
}

OptionContainer NotDoAnythingOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    Q_UNUSED(json)
    return {};
}

int NotDoAnythingOptionWidget::optionJsonVersion() const
{
    return 1;
}

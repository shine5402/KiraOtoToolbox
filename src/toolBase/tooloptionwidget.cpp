#include "tooloptionwidget.h"
#include <QVBoxLayout>
#include <QLabel>

ToolOptionWidget::ToolOptionWidget(QWidget *parent) : QWidget(parent)
{

}

OptionContainer ToolOptionWidget::getOptions() const
{
    Q_UNREACHABLE();
    return {};
}

void ToolOptionWidget::setOptions(const OptionContainer& options)
{
    Q_UNREACHABLE();
    Q_UNUSED(options)
}

QJsonObject ToolOptionWidget::getOptionsJson() const
{
    return optionsToJson(getOptions());
}

void ToolOptionWidget::setOptionsJson(const QJsonObject& json)
{
    setOptions(jsonToOptions(json));
}

QJsonObject ToolOptionWidget::optionsToJson(const OptionContainer& options) const
{
    Q_UNREACHABLE();
    Q_UNUSED(options);
}

OptionContainer ToolOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    Q_UNREACHABLE();
    Q_UNUSED(json);
}

int ToolOptionWidget::optionJsonVersion() const
{
    Q_UNREACHABLE();
}

QJsonObject ToolOptionWidget::updateOptionJsonFrom(int version, const QJsonObject& json) const
{
    Q_UNUSED(version);
    return json;
}

EmptyToolOptionWidget::EmptyToolOptionWidget(QWidget* parent) : ToolOptionWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    setLayout(layout);
    auto label = new QLabel(tr("There is nothing to configure."), this);
    layout->addStretch(1);
    layout->addWidget(label);
    layout->addStretch(1);
}

OptionContainer EmptyToolOptionWidget::getOptions() const
{
    return {};
}

void EmptyToolOptionWidget::setOptions(const OptionContainer& options)
{
    Q_UNUSED(options)
}

int EmptyToolOptionWidget::optionJsonVersion() const
{
    return 1;
}

QJsonObject EmptyToolOptionWidget::optionsToJson(const OptionContainer& options) const
{
    Q_UNUSED(options);
    Q_UNREACHABLE();
}

OptionContainer EmptyToolOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    Q_UNUSED(json);
    Q_UNREACHABLE();
}

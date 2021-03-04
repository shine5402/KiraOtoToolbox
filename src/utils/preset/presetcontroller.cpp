#include "presetcontroller.h"
#include "presetwidget.h"

PresetController::PresetController(QObject *parent) : QObject(parent)
{
}

PresetWidget* PresetController::getPresetWidget() const
{
    return presetWidget;
}

void PresetController::setPresetWidget(PresetWidget* value)
{
    presetWidget = value;
}

void PresetController::connectWithWidget()
{
    connect(presetWidget, &PresetWidget::extendEditAsked, this, &PresetController::showExtendEdit);

}

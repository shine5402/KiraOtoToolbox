#include "stringlistpresetcontroller.h"

StringListPresetController::StringListPresetController(PresetWidget* presetWidget, Preset preset, QObject* parent) :
    PresetController(presetWidget, parent), preset(preset)
{

}

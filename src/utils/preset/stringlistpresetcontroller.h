#ifndef STRINGLISTPRESETCONTROLLER_H
#define STRINGLISTPRESETCONTROLLER_H

#include "presetcontroller.h"
#include "preset.h"
#include "stringlistpreset.h"

class StringListPresetController : public PresetController
{
    Q_OBJECT
public:
    StringListPresetController(PresetWidget* presetWidget, Preset preset, QObject* parent = nullptr);

    // PresetController interface
protected slots:
    void showExtendEdit(PresetWidget* presetWidget);
    void endExtendEdit(Preset preset);

private:
    QVector<StringListPreset> presets;
};

#endif // STRINGLISTPRESETCONTROLLER_H

#ifndef PRESETWIDGETCONTAINER_H
#define PRESETWIDGETCONTAINER_H

#include <QWidget>
#include "presetmanager.h"
#include "optioncontainer.h"

namespace Ui {
    class PresetWidgetContainer;
}

class ToolOptionWidget;

class PresetWidgetContainer : public QWidget
{
    Q_OBJECT

public:
    explicit PresetWidgetContainer(const QMetaObject& optionWidgetMetaObj, QWidget *parent = nullptr);
    ~PresetWidgetContainer();

    ToolOptionWidget* optionWidget() const;

    //This function would override working options, and make state dirty. Used by chain tool.
    void setWorkingOptions(OptionContainer options);

private slots:
    void resetToPreset();
    void renamePreset();
    void savePreset();//or updatePreset()?
    void addPreset();
    void deletePreset();
    void importPreset();
    void exportPreset();
    void resetComboBoxDirtyState();
    void doResetToPreset();

private:
    QString targetName() const;
    Ui::PresetWidgetContainer *ui;
    QMetaObject optionWidgetMetaObj;
    ToolOptionWidget* optionWidget_;

    void reloadComboBoxItems();

    bool currentDirty();
    void setCurrentDirty(bool value);
    void setComboBoxItemTextDirtyState(int id, bool dirty);
    Preset getCurrentPreset() const;
    bool isCurrentPresetBuiltIn() const;
    bool checkCurrentPresetBuiltIn();//Would warn user about check result
    void doSavePreset();
};

#endif // PRESETWIDGETCONTAINER_H

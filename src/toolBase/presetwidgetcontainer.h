#ifndef PRESETWIDGETCONTAINER_H
#define PRESETWIDGETCONTAINER_H

#include <QWidget>
#include "presetmanager.h"

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

private slots:
    void resetToPreset();
    void renamePreset();
    void savePreset();//or updatePreset()?
    void addPreset();
    void deletePreset();
    void importPreset();
    void exportPreset();
    void resetComboBoxDirtyState();

private:
    QString targetName() const;
    Ui::PresetWidgetContainer *ui;
    const QMetaObject& optionWidgetMetaObj;
    ToolOptionWidget* optionWidget_;

    void reloadComboBoxItems();

    bool currentDirty = false;
    void setCurrentDirty(bool value);
    void refreshComboBoxForDirtyState();
    void setComboBoxItemTextDirtyState(int id, bool dirty);

    Preset getCurrentPreset() const;
    bool isCurrentPresetBuiltIn() const;
    bool checkCurrentPresetBuiltIn();//Would warn user about check result
};

#endif // PRESETWIDGETCONTAINER_H

#ifndef PRESETCONTROLLER_H
#define PRESETCONTROLLER_H

#include <QObject>
#include "preset.h"

class PresetWidget;

class PresetController : public QObject
{
    Q_OBJECT
public:
    explicit PresetController(QObject *parent = nullptr);

    PresetWidget* getPresetWidget() const;
    void setPresetWidget(PresetWidget* value);

    virtual int presetCount() const = 0;
    virtual QString getPresetName(int index) const;
    QVariant getPresetContent(int index) const;

protected:
    void connectWithWidget();


protected slots:
    virtual void showExtendEdit(int index) = 0;
    virtual void endExtendEdit() = 0;
    virtual void copyPreset(int index) = 0;
    virtual void removePreset(int index) = 0;
    virtual void savePreset(int index, QVariant content);
    virtual void renamePreset(int index);

private:
    PresetWidget* presetWidget;


signals:
    void extendEditEnded(int index);
    void presetCopyed(int index);
    void presetRemoved(int index);
    void presetSaved(int index);
};

#endif // PRESETCONTROLLER_H

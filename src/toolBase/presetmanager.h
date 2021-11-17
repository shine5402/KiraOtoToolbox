#ifndef PRESETMANAGER_H
#define PRESETMANAGER_H

#include <QString>
#include <QJsonObject>

struct Preset
{
    QString name;
    QJsonObject content;
    int version;
    QDateTime lastModified;

    bool isBuiltIn() const;
};

class PresetManager
{
public:
    static PresetManager* getManager();

    QVector<Preset> presetsForTarget(const QString& targetName) const;

    bool exist(const QString& targetName, const QString& name) const;
    bool exist(const QString& targetName, const Preset& preset) const;
    bool isBuiltIn(const QString& targetName, const QString& name) const;
    bool isBuiltIn(const QString& targetName, const Preset& preset) const;
    bool appendPresetForTarget(const QString& targetName, const Preset& preset);
    bool removePresetForTarget(const QString& targetName, const QString& name);

    class AppDataCannotWrite : std::runtime_error {
    public:
        AppDataCannotWrite() : std::runtime_error("Cannot find a writable place to write app data."){};
    };

    class ErrorWhenOpenPresetFile : std::runtime_error {
    public:
        ErrorWhenOpenPresetFile() : std::runtime_error("Cannot open preset file."){};
    };

    class ErrorWhenWritePresetFile : std::runtime_error {
    public:
        ErrorWhenWritePresetFile() : std::runtime_error("Error occured when writing to preset file"){};
    };
private:
    PresetManager();
    QHash<QString, QVector<Preset>> builtInPresets;
    QHash<QString, QVector<Preset>> userPresets;//Map<targetName, presets>
    void loadPresets();
    void savePresets();

    static PresetManager* instance;
};

#endif // PRESETMANAGER_H

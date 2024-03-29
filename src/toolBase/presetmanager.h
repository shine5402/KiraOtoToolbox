#ifndef PRESETMANAGER_H
#define PRESETMANAGER_H

#include <QString>
#include <QJsonObject>

class ToolOptionWidget;

//TODO: maybe refractor to class later
struct Preset
{
    QString name;
    QHash<QString, QString> nameI18nMap;//locale name, name
    QString getI18nName(const QLocale& locale) const;
    QJsonObject content;
    int version = 0;
    QDateTime lastModified;

    Preset(){};
    Preset(QString name, QJsonObject content, int version, QDateTime lastModified);
    Preset(const QJsonObject& json);

    void updateMeta(ToolOptionWidget* optionWidget);
    static QJsonObject getJson(const Preset& preset);
    QJsonObject toJson() const;
    static Preset fromJson(const QJsonObject& json);
};

class PresetManager
{
public:
    static PresetManager* getManager();

    QVector<Preset> presets(const QString& targetName) const;

    bool exist(const QString& targetName, const QString& name) const;
    bool exist(const QString& targetName, const Preset& preset) const;
    bool isBuiltIn(const QString& targetName, const QString& name) const;
    bool isBuiltIn(const QString& targetName, const Preset& preset) const;
    bool appendPreset(const QString& targetName, const Preset& preset);
    bool removePreset(const QString& targetName, const QString& name);
    bool replacePreset(const QString& targetName, const Preset& value);//or update
    bool replacePreset(const QString& targetName, const QString& name, const Preset& value);

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

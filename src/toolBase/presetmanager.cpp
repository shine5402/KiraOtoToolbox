#include "presetmanager.h"
#include <QStandardPaths>
#include <QDir>
#include "utils/misc/fplusAdapter.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QCoreApplication>
#include "tooloptionwidget.h"

PresetManager* PresetManager::instance = nullptr;

static constexpr auto BUILTIN_PRESET_FILE_PATH = ":/presets.json";

static auto presetNameEqual = [](const Preset& preset, const QString& name)->bool{
    return preset.name == name;
};

using namespace std::placeholders;

PresetManager* PresetManager::getManager()
{
    if (!instance)
        instance = new PresetManager;
    return instance;
}

QVector<Preset> PresetManager::presets(const QString& targetName) const
{
    QVector<Preset> result;
    //Add default
    result.append({QCoreApplication::translate("PresetManager", "Default"), {}, {}, {}});

    result.append(builtInPresets.value(targetName));
    result.append(userPresets.value(targetName));

    return result;
}

bool PresetManager::exist(const QString& targetName, const QString& name) const
{
    auto inBuiltIn = !fplus::keep_if(std::bind(presetNameEqual, _1, name), builtInPresets.value(targetName)).empty();
    auto inUser = !fplus::keep_if(std::bind(presetNameEqual, _1, name), userPresets.value(targetName)).empty();

    return inBuiltIn || inUser;
}

bool PresetManager::exist(const QString& targetName, const Preset& preset) const
{
    return exist(targetName, preset.name);
}

bool PresetManager::isBuiltIn(const QString& targetName, const QString& name) const
{
    auto inBuiltIn = !fplus::keep_if(std::bind(presetNameEqual, _1, name), builtInPresets.value(targetName)).empty();
    auto isDefault = name == QCoreApplication::translate("PresetManager", "Default");
    return inBuiltIn || isDefault;
}

bool PresetManager::isBuiltIn(const QString& targetName, const Preset& preset) const
{
    return isBuiltIn(targetName, preset.name);
}

bool PresetManager::appendPreset(const QString& targetName, const Preset& preset)
{
    if (exist(targetName, preset))
        return false;
    if (!userPresets.contains(targetName))
        userPresets.insert(targetName, {});
    userPresets.find(targetName).value().append(preset);
    savePresets();
    return true;
}

bool PresetManager::removePreset(const QString& targetName, const QString& name)
{
    if (!exist(targetName, name) || isBuiltIn(targetName, name))
        return false;
    //As we check the existance of the element, we should be fine with a direct unsafe_get_just, or there must be a bug.
    userPresets.find(targetName)->remove(fplus::find_first_idx_by(std::bind(presetNameEqual, _1, name), userPresets.value(targetName)).unsafe_get_just());
    savePresets();
    return true;
}

bool PresetManager::replacePreset(const QString& targetName, const Preset& value)
{
    return replacePreset(targetName, value.name, value);
}

bool PresetManager::replacePreset(const QString& targetName, const QString& name, const Preset& value)
{
    if (!exist(targetName, name) || isBuiltIn(targetName, name))
        return false;
    userPresets.find(targetName)->replace(fplus::find_first_idx_by(std::bind(presetNameEqual, _1, name), userPresets.value(targetName)).unsafe_get_just(), value);
    savePresets();
    return true;
}

PresetManager::PresetManager()
{
    loadPresets();
}

QHash<QString, QVector<Preset>> parsePresetJson(const QByteArray& jsonContent){
    auto jsonDoc = QJsonDocument::fromJson(jsonContent);
    auto root = jsonDoc.array();
    QHash<QString, QVector<Preset>> result;
    for (const auto& targetVal : root){
        auto targetObj = targetVal.toObject();
        auto targetName = targetObj.value("targetName").toString();
        auto presetArray = targetObj.value("presets").toArray();
        QVector<Preset> presetsForTarget;
        for (const auto& presetVal : presetArray){
            auto presetObj = presetVal.toObject();
            presetsForTarget.append(Preset::fromJson(presetObj));
        }
        result.insert(targetName, presetsForTarget);
    }
    return result;
}

void combinePresetMap(QHash<QString, QVector<Preset>>& dst, const QHash<QString, QVector<Preset>>& src){
    for (auto it = src.begin(); it != src.end(); ++it){
        if (dst.contains(it.key())){
            auto& dstContent = dst.find(it.key()).value();
            dstContent.append(it.value());
        }
        else {
            dst.insert(it.key(), it.value());
        }
    }
}

void PresetManager::loadPresets()
{
    //Load built-in
    //TODO: make built-in presets have i18n support
    QFile builtInPresetFile(BUILTIN_PRESET_FILE_PATH);
    if (builtInPresetFile.open(QFile::Text | QFile::ReadOnly)){
        builtInPresets = parsePresetJson(builtInPresetFile.readAll());
    }
    //Load user preset
    QFile userPresetFile = QFile{QStandardPaths::locate(QStandardPaths::AppDataLocation, "presets.json")};
    if (userPresetFile.open(QFile::Text | QFile::ReadOnly)){
        userPresets = parsePresetJson(userPresetFile.readAll());
    }
}

void PresetManager::savePresets()
{
    auto appDataDirPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (appDataDirPath.isEmpty()){
        throw AppDataCannotWrite{};
    }
    auto appDataDir = QDir(appDataDirPath);
    appDataDir.mkpath(".");//To prevent non-existence of the data dir.
    auto configFile = QFile(appDataDir.filePath("presets.json"));
    if (!configFile.open(QFile::WriteOnly | QFile::Text)){
        throw ErrorWhenOpenPresetFile{};
    }
    QJsonArray root;
    for (auto it = userPresets.begin(); it != userPresets.end(); ++it){
        auto currUserPresets = fplus::drop_if([it, this](const Preset& preset)->bool{
            return isBuiltIn(it.key(), preset);
        }, it.value());
        QJsonArray presetArray;
        for (const auto& i : currUserPresets){
            presetArray.append(i.toJson());
        }
        QJsonObject currObj;
        currObj.insert("targetName", it.key());
        currObj.insert("presets", presetArray);
        root.append(currObj);
    }
    if(configFile.write(QJsonDocument{root}.toJson()) == -1){
        throw ErrorWhenWritePresetFile{};
    }
}

Preset::Preset(QString name, QJsonObject content, int version, QDateTime lastModified):
    name(std::move(name)), content(std::move(content)), lastModified(std::move(lastModified))
{
    this->version = version;
}

Preset::Preset(const QJsonObject& json)
{
    *this = fromJson(json);
}

void Preset::updateMeta(ToolOptionWidget* optionWidget)
{
    version = optionWidget->optionJsonVersion();
    lastModified = QDateTime::currentDateTime();
}

QJsonObject Preset::getJson(const Preset& preset)
{
    QJsonObject presetObj;
    presetObj.insert("name", preset.name);
    presetObj.insert("version", preset.version);
    presetObj.insert("lastModified", preset.lastModified.toString(Qt::ISODate));
    presetObj.insert("content", preset.content);
    return presetObj;
}

QJsonObject Preset::toJson() const
{
    return getJson(*this);
}

Preset Preset::fromJson(const QJsonObject& json)
{
    Preset preset;
    preset.name = json.value("name").toString();
    preset.version = json.value("version").toInt();
    preset.lastModified = QDateTime::fromString(json.value("lastModified").toString(), Qt::ISODate);
    preset.content = json.value("content").toObject();
    return preset;
}


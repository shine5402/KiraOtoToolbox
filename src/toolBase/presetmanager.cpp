#include "presetmanager.h"
#include <QStandardPaths>
#include <QDir>
#include "utils/misc/fplusAdapter.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QCoreApplication>

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

QVector<Preset> PresetManager::presetsForTarget(const QString& targetName) const
{
    QVector<Preset> result;
    //Add default
    result.append({QCoreApplication::translate("PresetManager", "默认"), {}, {}, {}});

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

    return inBuiltIn;
}

bool PresetManager::isBuiltIn(const QString& targetName, const Preset& preset) const
{
    return isBuiltIn(targetName, preset.name);
}

bool PresetManager::appendPresetForTarget(const QString& targetName, const Preset& preset)
{
    if (exist(targetName, preset))
        return false;
    userPresets.find(targetName).value().append(preset);
    return true;
}

bool PresetManager::removePresetForTarget(const QString& targetName, const QString& name)
{
    if (!exist(targetName, name) || isBuiltIn(targetName, name))
        return false;
    //As we check the existance of the element, we should be fine with a direct unsafe_get_just, or there must be a bug.
    userPresets.find(targetName)->remove(fplus::find_first_idx_by(std::bind(presetNameEqual, _1, name), userPresets.value(targetName)).unsafe_get_just());
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
            Preset preset;
            preset.name = presetObj.value("name").toString();
            preset.version = presetObj.value("version").toInt();
            preset.lastModified = QDateTime::fromString(presetObj.value("lastModified").toString(), Qt::ISODate);
            preset.content = presetObj.value("content").toObject();
            presetsForTarget.append(preset);
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
            QJsonObject presetObj;
            presetObj.insert("name", i.name);
            presetObj.insert("version", i.version);
            presetObj.insert("lastModified", i.lastModified.toString(Qt::ISODate));
            presetObj.insert("content", i.content);
            presetArray.append(presetObj);
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

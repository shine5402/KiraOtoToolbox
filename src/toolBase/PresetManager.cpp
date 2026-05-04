#include "PresetManager.h"

#include <QCoreApplication>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QStandardPaths>

#include <algorithm>
#include <ranges>

#include "ToolOptionWidget.h"

PresetManager *PresetManager::instance = nullptr;

static constexpr auto BUILTIN_PRESET_FILE_PATH = ":/presets.json";

static auto presetNameEqual = [](const Preset &preset, const QString &name) -> bool {
    return preset.name == name;
};

PresetManager *PresetManager::getManager()
{
    if (!instance)
        instance = new PresetManager;
    return instance;
}

QVector<Preset> PresetManager::presets(const QString &targetName) const
{
    QVector<Preset> result;
    // Add default
    result.append({QCoreApplication::translate("PresetManager", "Default"), {}, {}, {}});

    result.append(builtInPresets.value(targetName));
    result.append(userPresets.value(targetName));

    return result;
}

bool PresetManager::exist(const QString &targetName, const QString &name) const
{
    const auto &builtInList = builtInPresets.value(targetName);
    const auto &userList = userPresets.value(targetName);
    auto inBuiltIn = std::ranges::find_if(builtInList, [&](const Preset &p) { return p.name == name; }) !=
                     builtInList.end();
    auto inUser = std::ranges::find_if(userList, [&](const Preset &p) { return p.name == name; }) != userList.end();

    return inBuiltIn || inUser;
}

bool PresetManager::exist(const QString &targetName, const Preset &preset) const
{
    return exist(targetName, preset.name);
}

bool PresetManager::isBuiltIn(const QString &targetName, const QString &name) const
{
    const auto &builtInList = builtInPresets.value(targetName);
    auto inBuiltIn = std::ranges::find_if(builtInList, [&](const Preset &p) { return p.name == name; }) !=
                     builtInList.end();
    auto isDefault = name == QCoreApplication::translate("PresetManager", "Default");
    return inBuiltIn || isDefault;
}

bool PresetManager::isBuiltIn(const QString &targetName, const Preset &preset) const
{
    return isBuiltIn(targetName, preset.name);
}

bool PresetManager::appendPreset(const QString &targetName, const Preset &preset)
{
    if (exist(targetName, preset))
        return false;
    if (!userPresets.contains(targetName))
        userPresets.insert(targetName, {});
    userPresets.find(targetName).value().append(preset);
    savePresets();
    return true;
}

bool PresetManager::removePreset(const QString &targetName, const QString &name)
{
    if (!exist(targetName, name) || isBuiltIn(targetName, name))
        return false;
    // As we check the existance of the element, we should be fine with a direct unsafe_get_just, or there must be a
    // bug.
    auto &userPresetList = userPresets.find(targetName).value();
    auto idx = std::distance(
        userPresetList.begin(),
        std::ranges::find_if(userPresetList, [&](const Preset &p) { return p.name == name; }));
    userPresetList.remove(idx);
    savePresets();
    return true;
}

bool PresetManager::replacePreset(const QString &targetName, const Preset &value)
{
    return replacePreset(targetName, value.name, value);
}

bool PresetManager::replacePreset(const QString &targetName, const QString &name, const Preset &value)
{
    if (!exist(targetName, name) || isBuiltIn(targetName, name))
        return false;
    auto &userPresetList = userPresets.find(targetName).value();
    auto idx = std::distance(
        userPresetList.begin(),
        std::ranges::find_if(userPresetList, [&](const Preset &p) { return p.name == name; }));
    userPresetList.replace(idx, value);
    savePresets();
    return true;
}

PresetManager::PresetManager()
{
    loadPresets();
}

QHash<QString, QVector<Preset>> parsePresetJson(const QByteArray &jsonContent)
{
    auto jsonDoc = QJsonDocument::fromJson(jsonContent);
    auto root = jsonDoc.array();
    QHash<QString, QVector<Preset>> result;
    for (const auto &targetVal : root) {
        auto targetObj = targetVal.toObject();
        auto targetName = targetObj.value("targetName").toString();
        auto presetArray = targetObj.value("presets").toArray();
        QVector<Preset> presetsForTarget;
        for (const auto &presetVal : presetArray) {
            auto presetObj = presetVal.toObject();
            presetsForTarget.append(Preset::fromJson(presetObj));
        }
        result.insert(targetName, presetsForTarget);
    }
    return result;
}

void combinePresetMap(QHash<QString, QVector<Preset>> &dst, const QHash<QString, QVector<Preset>> &src)
{
    for (auto it = src.begin(); it != src.end(); ++it) {
        if (dst.contains(it.key())) {
            auto &dstContent = dst.find(it.key()).value();
            dstContent.append(it.value());
        } else {
            dst.insert(it.key(), it.value());
        }
    }
}

void PresetManager::loadPresets()
{
    // Load built-in
    QFile builtInPresetFile(BUILTIN_PRESET_FILE_PATH);
    if (builtInPresetFile.open(QFile::Text | QFile::ReadOnly)) {
        builtInPresets = parsePresetJson(builtInPresetFile.readAll());
    }
    // Load user preset
    QFile userPresetFile = QFile{QStandardPaths::locate(QStandardPaths::AppDataLocation, "presets.json")};
    if (userPresetFile.open(QFile::Text | QFile::ReadOnly)) {
        userPresets = parsePresetJson(userPresetFile.readAll());
    }
}

void PresetManager::savePresets()
{
    auto appDataDirPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (appDataDirPath.isEmpty()) {
        throw AppDataCannotWrite{};
    }
    auto appDataDir = QDir(appDataDirPath);
    appDataDir.mkpath("."); // To prevent non-existence of the data dir.
    auto configFile = QFile(appDataDir.filePath("presets.json"));
    if (!configFile.open(QFile::WriteOnly | QFile::Text)) {
        throw ErrorWhenOpenPresetFile{};
    }
    QJsonArray root;
    for (auto it = userPresets.begin(); it != userPresets.end(); ++it) {
        auto currUserPresets =
            it.value() |
            std::views::filter(
                [it, this](const Preset &preset) -> bool { return !isBuiltIn(it.key(), preset); }) |
            std::ranges::to<QVector<Preset>>();
        QJsonArray presetArray;
        for (const auto &i : currUserPresets) {
            presetArray.append(i.toJson());
        }
        QJsonObject currObj;
        currObj.insert("targetName", it.key());
        currObj.insert("presets", presetArray);
        root.append(currObj);
    }
    if (configFile.write(QJsonDocument{root}.toJson()) == -1) {
        throw ErrorWhenWritePresetFile{};
    }
}

QString Preset::getI18nName(const QLocale &locale) const
{
    auto uiLang = locale.uiLanguages();
    for (const auto &l : qAsConst(uiLang)) {
        if (nameI18nMap.contains(l))
            return nameI18nMap.value(l);
    }

    return name;
}

Preset::Preset(QString name, QJsonObject content, int version, QDateTime lastModified)
    : name(std::move(name)), content(std::move(content)), lastModified(std::move(lastModified))
{
    this->version = version;
}

Preset::Preset(const QJsonObject &json)
{
    *this = fromJson(json);
}

void Preset::updateMeta(ToolOptionWidget *optionWidget)
{
    version = optionWidget->optionJsonVersion();
    lastModified = QDateTime::currentDateTime();
}

QJsonObject Preset::getJson(const Preset &preset)
{
    QJsonObject presetObj;
    presetObj.insert("name", preset.name);
    for (auto it = preset.nameI18nMap.begin(); it != preset.nameI18nMap.end(); ++it) {
        presetObj.insert("name_" + it.key(), it.value());
    }
    presetObj.insert("version", preset.version);
    presetObj.insert("lastModified", preset.lastModified.toString(Qt::ISODate));
    presetObj.insert("content", preset.content);
    return presetObj;
}

QJsonObject Preset::toJson() const
{
    return getJson(*this);
}

Preset Preset::fromJson(const QJsonObject &json)
{
    Preset preset;
    preset.name = json.value("name").toString();
    const auto variantMap = json.toVariantMap();
    QVariantMap i18n;
    for (auto it = variantMap.begin(); it != variantMap.end(); ++it) {
        if (it.key().startsWith("name_"))
            i18n.insert(it.key(), it.value());
    }
    for (auto it = i18n.begin(); it != i18n.end(); ++it) {
        auto key = it.key();
        key.remove(0, 5);
        preset.nameI18nMap.insert(key, it.value().toString());
    }
    preset.version = json.value("version").toInt();
    preset.lastModified = QDateTime::fromString(json.value("lastModified").toString(), Qt::ISODate);
    preset.content = json.value("content").toObject();
    return preset;
}

#include "translationmanager.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <utils/misc/fplusAdapter.h>

TranslationManager* TranslationManager::instance = nullptr;

TranslationManager* TranslationManager::getManager()
{
    if (!instance)
        instance = new TranslationManager;
    return instance;
}

TranslationManager::TranslationManager()
{
    auto metaFilePath = QDir{qApp->applicationDirPath()}.filePath("translations/translations.json");
    auto metaFile = QFile{metaFilePath};
    if (!metaFile.open(QFile::Text | QFile::ReadOnly))
        return;
    auto metaFileContent = metaFile.readAll();
    auto array = QJsonDocument::fromJson(metaFileContent).array();
    translations = fplus::keep_if([](const Translation& elem)->bool{
        return elem.isValid();
    }, fplus::transform([](const QJsonValue& value)->Translation{
        return Translation::fromJson(value.toObject());
    }, array));
}

QVector<Translation> TranslationManager::getTranslations() const
{
    return translations;
}

Translation TranslationManager::getTranslationFor(QLocale locale) const
{
    return fplus::get_just_or_default(fplus::find_first_by([locale](const Translation& translation)->bool{
        return translation.locale() == locale;
    }, translations));
}

int TranslationManager::getCurrentInstalledTranslationID() const
{
    auto result = fplus::find_first_idx_by([](const Translation& elem)->bool{
        return elem.getIDString() == Translation::getCurrentInstalledTranslationIDString();
    }, translations);
    return result.is_just() ? result.unsafe_get_just() : -1;
}

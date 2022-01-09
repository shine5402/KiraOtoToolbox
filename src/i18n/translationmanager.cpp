#include "translationmanager.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <utils/misc/fplusAdapter.h>
#include <QAction>
#include <QObject>
#include <QSettings>

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
        auto tr = Translation::fromJson(value.toObject());
        tr.setTranslationFilenames(fplus::transform([](const QString& fileName)->QString{
            return QDir{qApp->applicationDirPath()}.filePath("translations/" + fileName);
        },
        tr.translationFilenames()));
        return tr;
    }, array));

    getTranslationFor(getLocaleUserSetting()).install();
}

void TranslationManager::setLangActionChecked(QMenu* i18nMenu, const Translation& translation) const
{
    auto actions = i18nMenu->actions();
    for (auto action : qAsConst(actions)){
        auto currTr = TranslationManager::getManager()->getTranslation(action->data().toInt());
        action->setChecked(currTr == translation);
    }
}

void TranslationManager::saveUserLocaleSetting(QLocale locale)
{
    QSettings settings;
    settings.setValue("locale", locale);
}

QLocale TranslationManager::getLocaleUserSetting() const
{
    QSettings settings;
    return settings.value("locale", QLocale::system()).value<QLocale>();
}

QVector<Translation> TranslationManager::getTranslations() const
{
    return translations;
}

Translation TranslationManager::getTranslation(int i) const
{
    if (i == -1)
        return {};
    return translations.at(i);
}


Translation TranslationManager::getTranslationFor(const QLocale& locale) const
{
    return fplus::get_just_or_default(fplus::find_first_by([&locale](const Translation& translation)->bool{
        return translation.locale() == locale;
    }, translations));
}

int TranslationManager::getCurrentInstalledTranslationID() const
{
    auto result = fplus::find_first_idx_by([](const Translation& elem)->bool{
        return elem == Translation::getCurrentInstalled();
    }, translations);
    return result.is_just() ? result.unsafe_get_just() : -1;
}

Translation TranslationManager::getCurrentInstalled() const
{
    return Translation::getCurrentInstalled();
}

QMenu* TranslationManager::createI18nMenu(QWidget* parent) const
{
    auto translations = TranslationManager::getManager()->getTranslations();
    auto i18nMenu = new QMenu("Language", parent);
    auto defaultLang = new QAction("English, built-in", i18nMenu);
    defaultLang->setData(-1);
    defaultLang->setCheckable(true);
    i18nMenu->addAction(defaultLang);

    for (auto i = 0; i < translations.count(); ++i)
    {
        auto l = translations.at(i);
        auto langAction = new QAction(QLatin1String("%1 (%2), by %3").arg(QLocale::languageToString(l.locale().language()),l.locale().bcp47Name(),l.author()), i18nMenu);
        langAction->setData(i);
        langAction->setCheckable(true);
        i18nMenu->addAction(langAction);

    }
    QObject::connect(i18nMenu, &QMenu::triggered, i18nMenu, [this, i18nMenu](QAction* action){
        auto translation = getTranslation(action->data().toInt());
        translation.install();
        setLangActionChecked(i18nMenu, translation);
    });

    setLangActionChecked(i18nMenu, getCurrentInstalled());
    return i18nMenu;
}

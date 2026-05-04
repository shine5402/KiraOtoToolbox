#include "utils/i18n/TranslationManager.h"

#include <QAction>
#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <algorithm>

using namespace Qt::StringLiterals;

TranslationManager *TranslationManager::s_instance = nullptr;

TranslationManager *TranslationManager::getManager()
{
    if (!s_instance)
        s_instance = new TranslationManager;
    return s_instance;
}

TranslationManager::TranslationManager()
{
    // Enumerate available translations from the resource folder.
    // qt_add_translations() embeds .qm files as resources under :/i18n/.
    QDir i18nDir(":/i18n");
    QStringList qmFiles = i18nDir.entryList(QStringList() << "KiraOtoToolbox_*.qm", QDir::Files);

    for (const QString &fileName : qmFiles) {
        // Extract locale string from filename (e.g., "KiraOtoToolbox_zh_CN.qm" -> "zh_CN")
        QString localeName = fileName;
        localeName.remove("KiraOtoToolbox_").remove(".qm");

        QLocale locale(localeName);
        if (locale.language() != QLocale::C) {
            m_supportedLocales.append(locale);
        }
    }

    // Install user's preferred translation
    installTranslation(getLocaleUserSetting());
}

QList<QLocale> TranslationManager::supportedLocales() const
{
    return m_supportedLocales;
}

QLocale TranslationManager::currentLocale() const
{
    return m_currentLocale;
}

bool TranslationManager::installTranslation(const QLocale &locale)
{
    // Remove previous translator if any
    if (m_translator) {
        qApp->removeTranslator(m_translator);
        delete m_translator;
        m_translator = nullptr;
    }

    // If locale is not in supported list (or is default English), keep English
    bool isSupported = std::ranges::any_of(m_supportedLocales,
                                           [&locale](const QLocale &l) { return l.language() == locale.language(); });

    if (!isSupported) {
        m_currentLocale = QLocale(QLocale::English);
        return true;
    }

    // Load translation from embedded resources at :/i18n
    m_translator = new QTranslator(qApp);
    if (m_translator->load(locale, u"KiraOtoToolbox"_s, u"_"_s, u":/i18n"_s)) {
        qApp->installTranslator(m_translator);
        m_currentLocale = locale;
        return true;
    } else {
        qDebug() << "Failed to load translation for locale:" << locale.bcp47Name();
        delete m_translator;
        m_translator = nullptr;
        m_currentLocale = QLocale(QLocale::English);
        return false;
    }
}

void TranslationManager::setLangActionChecked(QMenu *i18nMenu, const QLocale &locale) const
{
    auto actions = i18nMenu->actions();
    for (auto action : std::as_const(actions)) {
        auto actionLocale = action->data().value<QLocale>();
        action->setChecked(actionLocale == locale);
    }
}

void TranslationManager::saveUserLocaleSetting(const QLocale &locale) const
{
    QSettings settings;
    settings.setValue("locale", locale);
}

QLocale TranslationManager::getLocaleUserSetting() const
{
    QSettings settings;
    return settings.value("locale", QLocale::system()).value<QLocale>();
}

QMenu *TranslationManager::getI18nMenu()
{
    if (m_i18nMenu)
        return m_i18nMenu;

    m_i18nMenu = new QMenu("Language");

    // Add supported translations
    for (const auto &locale : std::as_const(m_supportedLocales)) {
        auto getActionText = [&](const QLocale &loc) {
            if (loc.language() == QLocale::English) {
                return QStringLiteral("English (%1) (%2)")
                    .arg(QLocale::territoryToString(loc.territory()), loc.bcp47Name());
            }
            return QStringLiteral("%1 [%2] (%3)")
                .arg(QLocale::languageToString(loc.language()), loc.nativeLanguageName(), loc.bcp47Name());
        };

        auto langAction = new QAction(getActionText(locale), m_i18nMenu);
        langAction->setData(QVariant::fromValue(locale));
        langAction->setCheckable(true);
        m_i18nMenu->addAction(langAction);
    }

    QObject::connect(m_i18nMenu, &QMenu::triggered, m_i18nMenu, [this](QAction *action) {
        auto locale = action->data().value<QLocale>();
        installTranslation(locale);
        setLangActionChecked(m_i18nMenu, locale);
        saveUserLocaleSetting(locale);
    });

    setLangActionChecked(m_i18nMenu, m_currentLocale);
    return m_i18nMenu;
}

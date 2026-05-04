#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H

#include <QLocale>
#include <QMenu>
#include <QTranslator>

class TranslationManager
{
public:
    /*
     * TranslationManager will store user's i18n preference with default constructed QSettings.
     * And it will install user's preferred translation when getManager() being called first time.
     * So don't forget to set Application's name and organization before first call.
     */
    static TranslationManager *getManager();

    QList<QLocale> supportedLocales() const;
    QLocale currentLocale() const;
    bool installTranslation(const QLocale &locale);

    QMenu *getI18nMenu();

private:
    static TranslationManager *s_instance;
    TranslationManager();
    void setLangActionChecked(QMenu *i18nMenu, const QLocale &locale) const;
    void saveUserLocaleSetting(const QLocale &locale) const;
    QLocale getLocaleUserSetting() const;

    QMenu *m_i18nMenu = nullptr;
    QList<QLocale> m_supportedLocales;
    QLocale m_currentLocale;
    QTranslator *m_translator = nullptr;
};

#endif // TRANSLATIONMANAGER_H

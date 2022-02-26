#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H
#include "translation.h"
#include <QMenu>

class TranslationManager
{
public:
    /*
     * TranslationManager will store user's i18n preference with default constructed QSettings.
     * And it will install user's preferred translation when getManager() being called first time.
     * So don't forget to set Application's name and organization before first call.
     */
    static TranslationManager* getManager();

    QVector<Translation> getTranslations() const;
    Translation getTranslation(int i) const;
    Translation getTranslationFor(const QLocale& locale) const;
    int getCurrentInstalledTranslationID() const;
    Translation getCurrentInstalled() const;

    QMenu* getI18nMenu();

private:
    static TranslationManager* instance;
    TranslationManager();
    QMenu* i18nMenu = nullptr;

    QVector<Translation> translations;

    void setLangActionChecked(QMenu* i18nMenu, const Translation& translation) const;
    void saveUserLocaleSetting(QLocale locale) const;
    QLocale getLocaleUserSetting() const;
};



#endif // TRANSLATIONMANAGER_H

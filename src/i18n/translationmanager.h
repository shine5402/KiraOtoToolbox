#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H
#include "translation.h"
#include <QMenu>

class TranslationManager
{
public:
    static TranslationManager* getManager();

    QVector<Translation> getTranslations() const;
    Translation getTranslation(int i) const;
    Translation getTranslationFor(const QLocale& locale) const;
    int getCurrentInstalledTranslationID() const;
    Translation getCurrentInstalled() const;

    QMenu* createI18nMenu(QWidget* parent = nullptr) const;

private:
    static TranslationManager* instance;
    TranslationManager();

    QVector<Translation> translations;

    void setLangActionChecked(QMenu* i18nMenu, const Translation& translation) const;
    void saveUserLocaleSetting(QLocale locale);
    QLocale getLocaleUserSetting() const;
};

#endif // TRANSLATIONMANAGER_H

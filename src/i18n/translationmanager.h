#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H
#include "translation.h"

class TranslationManager
{
public:
    static TranslationManager* getManager();

    QVector<Translation> getTranslations() const;
    Translation getTranslation(int i) const;
    Translation getTranslationFor(const QLocale& locale) const;
    int getCurrentInstalledTranslationID() const;
    Translation getCurrentInstalled() const;

private:
    TranslationManager();
    QVector<Translation> translations;

    static TranslationManager* instance;
};

#endif // TRANSLATIONMANAGER_H

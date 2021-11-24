#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H
#include "translation.h"

class TranslationManager
{
public:
    static TranslationManager* getManager();

    QVector<Translation> getTranslations() const;
    Translation getTranslationFor(QLocale locale) const;
    int getCurrentInstalledTranslationID() const;

private:
    TranslationManager();
    QVector<Translation> translations;

    static TranslationManager* instance;
};

#endif // TRANSLATIONMANAGER_H

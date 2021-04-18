#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QObject>
#include <QLocale>
#include <QTranslator>

class Translation : public QObject
{
    Q_OBJECT
public:
    explicit Translation(QLocale locale, QStringList translationFilenames, QString author, QObject *parent = nullptr);

private:
    QLocale locale;
    QStringList translationFilenames;
    QString author;
};

#endif // TRANSLATION_H

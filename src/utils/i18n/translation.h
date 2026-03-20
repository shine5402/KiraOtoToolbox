#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QObject>
#include <QLocale>
#include <QTranslator>

class Translation
{
public:
    Translation(QLocale locale, QStringList translationFilenames, QString author);
    Translation();

    QJsonObject toJson() const;
    static Translation fromJson(const QJsonObject& jsonDoc);

    void install() const;
    static void uninstall();

    QLocale locale() const;
    void setLocale(const QLocale& value);

    QStringList translationFilenames() const;
    void setTranslationFilenames(const QStringList& value);

    QString author() const;
    void setAuthor(const QString& value);

    static Translation getCurrentInstalled();

    bool isValid() const;

    bool operator==(const Translation& other) const;

private:
    QLocale locale_ = QLocale("en_US");
    QStringList translationFilenames_;
    QString author_;

    static QList<QTranslator*> installedTranslators;
    static Translation currentInstalled;
};

#endif // TRANSLATION_H

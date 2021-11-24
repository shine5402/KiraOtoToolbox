#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QObject>
#include <QLocale>
#include <QTranslator>

class Translation : public QObject
{
    Q_OBJECT
public:
    Translation(QLocale locale, QStringList translationFilenames, QString author, QObject *parent = nullptr);
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

    QString getIDString() const;

    static QString getCurrentInstalledTranslationIDString();

    bool isValid() const;

private:
    QLocale locale_;
    QStringList translationFilenames_;
    QString author_;
    bool valid = false;

    static QList<QTranslator*> installedTranslators;
    static QString currentInstalledTranslationIDString;
};

#endif // TRANSLATION_H

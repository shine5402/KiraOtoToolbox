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

    QJsonDocument toJsonDoc() const;
    static Translation fromJsonDoc(const QJsonDocument& jsonDoc);

    void install() const;
private:
    QLocale locale;
    QStringList translationFilenames;
    QString author;

    static QList<QTranslator*> installedTranslators;
};

#endif // TRANSLATION_H

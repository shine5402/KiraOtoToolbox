#include "translation.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <fplus/fplus.hpp>
#include "utils/misc/fplusAdapter.h"
#include <QApplication>

Translation::Translation(QLocale locale, QStringList translationFilenames, QString author, QObject *parent)
    : QObject(parent), locale(locale), translationFilenames(translationFilenames), author(author)
{
    valid = true;
}

Translation::Translation()
{

}

QList<QTranslator*> Translation::installedTranslators;

QJsonObject Translation::toJson() const
{
    QJsonObject root;
    root.insert("locale", locale.bcp47Name());
    root.insert("translationFilenames", QJsonArray::fromStringList(translationFilenames));
    root.insert("author", author);
    return root;
}

Translation Translation::fromJson(const QJsonObject& json)
{
    if (json.empty() || !json.contains("locale") || !json.contains("translationFilenames") || !json.contains("author"))
        return {};

    auto locale = QLocale(json.value("locale").toString());
    auto translationFilenames = fplus::transform([](const QJsonValue& value)->QString{
        return value.toString();
    }, json.value("translationFilenames").toArray()).toList();
    auto author = json.value("author").toString();

    return Translation(locale, translationFilenames, author);
}

void Translation::install() const
{
    uninstall();

    for (const auto &fileName : std::as_const(translationFilenames)){
        auto translator = new QTranslator(qApp);
        translator->load(fileName);
        qApp->installTranslator(translator);
        installedTranslators.append(translator);
        currentInstalledTranslationIDString = getIDString();
    }
}

void Translation::uninstall()
{
    currentInstalledTranslationIDString.clear();
    for (auto translator : std::as_const(installedTranslators)){
        qApp->removeTranslator(translator);
    }
}

QLocale Translation::getLocale() const
{
    return locale;
}

void Translation::setLocale(const QLocale& value)
{
    locale = value;
}

QStringList Translation::getTranslationFilenames() const
{
    return translationFilenames;
}

void Translation::setTranslationFilenames(const QStringList& value)
{
    translationFilenames = value;
}

QString Translation::getAuthor() const
{
    return author;
}

void Translation::setAuthor(const QString& value)
{
    author = value;
}

QString Translation::getIDString() const
{
    return locale.name() + "_" + author;
}

QString Translation::getCurrentInstalledTranslationIDString()
{
    return currentInstalledTranslationIDString;
}

bool Translation::isValid() const
{
    return valid;
}

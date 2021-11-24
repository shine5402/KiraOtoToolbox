#include "translation.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <fplus/fplus.hpp>
#include "utils/misc/fplusAdapter.h"
#include <QApplication>

Translation::Translation(QLocale locale, QStringList translationFilenames, QString author)
    :locale_(locale), translationFilenames_(translationFilenames), author_(author)
{

}

Translation::Translation()
{

}

QList<QTranslator*> Translation::installedTranslators;
Translation Translation::currentInstalled;

QJsonObject Translation::toJson() const
{
    QJsonObject root;
    root.insert("locale", locale_.bcp47Name());
    root.insert("translationFilenames", QJsonArray::fromStringList(translationFilenames_));
    root.insert("author", author_);
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
    if (!isValid())
        return;

    for (const auto &fileName : std::as_const(translationFilenames_)){
        auto translator = new QTranslator(qApp);
        translator->load(fileName);
        qApp->installTranslator(translator);
        installedTranslators.append(translator);
        currentInstalled = *this;
    }
}

void Translation::uninstall()
{
    currentInstalled = {};
    for (auto translator : std::as_const(installedTranslators)){
        qApp->removeTranslator(translator);
    }
}

QLocale Translation::locale() const
{
    return locale_;
}

void Translation::setLocale(const QLocale& value)
{
    locale_ = value;
}

QStringList Translation::translationFilenames() const
{
    return translationFilenames_;
}

void Translation::setTranslationFilenames(const QStringList& value)
{
    translationFilenames_ = value;
}

QString Translation::author() const
{
    return author_;
}

void Translation::setAuthor(const QString& value)
{
    author_ = value;
}

Translation Translation::getCurrentInstalled()
{
    return currentInstalled;
}

bool Translation::isValid() const
{
    return translationFilenames_.isEmpty() || author_.isEmpty();
}

bool Translation::operator==(const Translation& other) const
{
    if (!isValid() && !other.isValid())
        return false;
    return locale_ == other.locale_ && translationFilenames_ == other.translationFilenames_ && author_ == other.author_;
}

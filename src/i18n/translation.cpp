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

}

QList<QTranslator*> Translation::installedTranslators;

QJsonDocument Translation::toJsonDoc() const
{
    QJsonObject root;
    root.insert("locale", locale.bcp47Name());
    root.insert("translationFilenames", QJsonArray::fromStringList(translationFilenames));
    root.insert("author", author);
    return QJsonDocument{root};
}

Translation Translation::fromJsonDoc(const QJsonDocument& jsonDoc)
{
    auto root = jsonDoc.object();
    auto locale = QLocale(root.value("locale").toString());
    auto translationFilenames = fplus::transform([](const QJsonValue& value)->QString{
        return value.toString();
    }, root.value("translationFilenames").toArray());
    auto author = root.value("author").toString();

    return Translation(locale, translationFilenames, author);
}

void Translation::install() const
{
    for (auto translator : std::as_const(installedTranslators)){
        qApp->removeTranslator(translator);
    }

    for (const auto &fileName : std::as_const(translationFilenames)){
        auto translator = new QTranslator(qApp);
        translator->load(fileName);
        qApp->installTranslator(translator);
        installedTranslators.append(translator);
    }
}

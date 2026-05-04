#include "utils/UpdateChecker.h"

#include <QCoreApplication>
#include <QDesktopServices>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSettings>
#include <QtDebug>

#include "utils/dialogs/CommonHtmlDialog.h"

namespace UpdateChecker {
QNetworkAccessManager *GithubReleaseChecker::s_networkMgr = new QNetworkAccessManager();

void GithubReleaseChecker::triggerUpdateCheck(QVersionNumber current)
{
    // Get version from application itself if not specified
    if (current.isNull()) {
        current = current.fromString(qApp->applicationVersion());
    }

    if (current.isNull()) {
        // If still null, it means that we are in development version, so we can skip the check
        qDebug() << "[Update checker] Current version is null, skip update check";
        return;
    }

    QNetworkRequest request;
    // Use Github v3 REST API explicitly, as recommended
    request.setRawHeader("Accept", "application/vnd.github.v3+json");
    request.setUrl(QStringLiteral("https://api.github.com/repos/%1/%2/releases/latest").arg(m_owner, m_repo));

    auto reply = s_networkMgr->get(request);

    connect(reply, &QNetworkReply::finished, reply, [reply, current, this]() {
        if (reply->error() != QNetworkReply::NoError) {
            emit errorOccurred(
                QCoreApplication::translate("UpdateChecker", "Network error occurred: %1").arg(reply->errorString()));
            reply->deleteLater();
            return;
        }

        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        auto json = jsonDoc.object();
        auto versionStr = json.value("tag_name").toString();
        versionStr.remove(0, 1); // remove "v" from "vX.x.x"
        auto latestVer = QVersionNumber::fromString(versionStr);
        qDebug() << "[Update checker] latest version=" << latestVer.toString()
                 << " where tag=" << json.value("tag_name").toString();
        if (latestVer > current) {
            auto msgBody = json.value("body").toString();
            auto url = json.value("html_url").toString();
            emit updateAvailable(latestVer, msgBody, url);
        } else
            emit alreadyUpToDate();

        reply->deleteLater();
    });
}

bool getAutoCheckEnabled()
{
    QSettings settings;
    // Migration: convert old schedule setting to boolean
    // Any value other than DISABLED (4) maps to enabled
    if (settings.contains("updateSchedule")) {
        int oldSchedule = settings.value("updateSchedule").toInt();
        bool enabled = (oldSchedule != 4); // 4 = DISABLED
        settings.remove("updateSchedule");
        settings.remove("updateLastChecked");
        settings.setValue("autoCheckEnabled", enabled);
        return enabled;
    }
    return settings.value("autoCheckEnabled", true).toBool();
}

void setAutoCheckEnabled(bool enabled)
{
    QSettings settings;
    settings.setValue("autoCheckEnabled", enabled);
}

QAction *createAutoCheckAction()
{
    auto action = new QAction(QCoreApplication::translate("UpdateChecker", "Auto check update on startup"));
    action->setCheckable(true);
    action->setChecked(getAutoCheckEnabled());

    QObject::connect(action, &QAction::triggered, action, [action](bool checked) { setAutoCheckEnabled(checked); });

    return action;
}

QDialog *getUpdateAvailableDialog(const QVersionNumber &newVersion, const QString &msgBody, const QUrl &updateUrl)
{
    auto dialog = new CommonHtmlDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(QCoreApplication::translate("UpdateChecker", "Update available"));
    dialog->setLabel(QCoreApplication::translate("UpdateChecker", "New version \"%1\" of \"%2\" is available. "
                                                                  "Currently you are at \"%3\".\n"
                                                                  "Open download page?")
                         .arg(newVersion.toString(), qApp->applicationName(), qApp->applicationVersion()));
    dialog->setAllowRemoteImageLoad(true);
    dialog->setMarkdown(msgBody);
    dialog->setStandardButtons(QDialogButtonBox::Yes | QDialogButtonBox::No);
    dialog->setWindowModality(Qt::ApplicationModal);
    QObject::connect(dialog, &QDialog::accepted, [=]() { QDesktopServices::openUrl(updateUrl); });
    return dialog;
};

void triggerScheduledCheck(Checker *checker)
{
    if (getAutoCheckEnabled()) {
        // To keep one responding on signal emitting,
        // we just disconnect all slots when operation done.
        QObject::connect(checker, &Checker::updateAvailable, checker,
                         [checker](const QVersionNumber &newVersion, const QString &msgBody, const QUrl &updateUrl) {
                             auto dialog = getUpdateAvailableDialog(newVersion, msgBody, updateUrl);
                             dialog->show();
                             checker->disconnect();
                         });
        QObject::connect(checker, &Checker::alreadyUpToDate, checker, [checker]() {
            // No need to notify user already up-to-date when auto checking
            checker->disconnect();
        });
        QObject::connect(checker, &Checker::errorOccurred, checker, [checker](const QString &msg) {
            qWarning("[Update checker] error when checking, %s", msg.toStdString().c_str());
            checker->disconnect();
        });
        checker->triggerUpdateCheck();
    }
}

void checkManually(Checker *checker)
{
    // To keep one responding on signal emitting,
    // we just disconnect all slots when operation done.
    QObject::connect(checker, &Checker::updateAvailable, checker,
                     [checker](const QVersionNumber &newVersion, const QString &msgBody, const QUrl &updateUrl) {
                         auto dialog = getUpdateAvailableDialog(newVersion, msgBody, updateUrl);
                         dialog->show();
                         checker->disconnect();
                     });
    QObject::connect(checker, &Checker::alreadyUpToDate, checker, [checker]() {
        QMessageBox::information(nullptr, {},
                                 QCoreApplication::translate("UpdateChecker", "You are already up-to-date."));
        checker->disconnect();
    });
    QObject::connect(checker, &Checker::errorOccurred, checker, [checker](const QString &msg) {
        QMessageBox::warning(
            nullptr, {},
            QCoreApplication::translate("UpdateChecker", "Error occurred when checking update: %1").arg(msg));
        qWarning("[Update checker] error when checking, %s", msg.toStdString().c_str());
        checker->disconnect();
    });
    checker->triggerUpdateCheck();
}

} // namespace UpdateChecker

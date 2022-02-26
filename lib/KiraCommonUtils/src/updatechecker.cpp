#include "kira/updatechecker.h"
#include <QNetworkAccessManager>
#include <QCoreApplication>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include "kira/dialogs/showhtmldialog.h"
#include <QDesktopServices>
#include <QMessageBox>
#include <QtDebug>

namespace UpdateChecker {
    QNetworkAccessManager* GithubReleaseChecker::networkMgr = new QNetworkAccessManager();

    void GithubReleaseChecker::triggerUpdateCheck(QVersionNumber current)
    {
        //Get version from application itself if not specified
        if (current.isNull()){
            current = current.fromString(qApp->applicationVersion());
        }

        QNetworkRequest request;
        //Use Github v3 REST API explicitly, as recommended
        request.setRawHeader("Accept", "application/vnd.github.v3+json");
        request.setUrl(QStringLiteral("https://api.github.com/repos/%1/%2/releases/latest").arg(owner, repo));

        auto reply = networkMgr->get(request);

        connect(reply, &QNetworkReply::finished, reply, [reply, current, this](){
            if (reply->error() != QNetworkReply::NoError){
                reply->deleteLater();
                return;
            }
            QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
            auto json = jsonDoc.object();
            auto versionStr = json.value("tag_name").toString();
            versionStr.remove(0, 1);//remove "v" from "vX.x.x"
            auto latestVer = QVersionNumber::fromString(versionStr);
            qDebug() << "[Update checker] lastest version=" << latestVer.toString() << " where tag=" << json.value("tag_name").toString();
            if (latestVer > current)
            {
                auto msgBody = json.value("body").toString();
                auto url = json.value("html_url").toString();
                emit updateAvailable(latestVer, msgBody, url);
            }
            else
                emit alreadyUpToDate();

            reply->deleteLater();
        });

        connect(reply, &QNetworkReply::errorOccurred, reply, [reply, this](){
            emit errorOccurred(reply->errorString());
            reply->deleteLater();
        });
    }

    Schedule getSchedule()
    {
        QSettings settings;
        return settings.value("updateSchedule", EVERYRUN).value<Schedule>();
    }

    void setSchedule(Schedule value)
    {
        QSettings settings;
        settings.setValue("updateSchedule", value);
    }

    QMenu* createMenuForSchedule()
    {
        auto menu = new QMenu(QCoreApplication::translate("UpdateChecker", "Check updates on"));
        auto everyRunAction = menu->addAction(QCoreApplication::translate("UpdateChecker", "Every run"));
        auto dailyAction = menu->addAction(QCoreApplication::translate("UpdateChecker", "Every day"));
        auto weeklyAction = menu->addAction(QCoreApplication::translate("UpdateChecker", "Every week"));
        auto monthlyAction = menu->addAction(QCoreApplication::translate("UpdateChecker", "Every month"));
        menu->addSeparator();
        auto disableAction = menu->addAction(QCoreApplication::translate("UpdateChecker", "Disable auto check"));

        everyRunAction->setCheckable(true);
        dailyAction->setCheckable(true);
        weeklyAction->setCheckable(true);
        monthlyAction->setCheckable(true);
        disableAction->setCheckable(true);

        auto refreshCheck = [=](){
            auto schedule = getSchedule();
            everyRunAction->setChecked(schedule == EVERYRUN);
            dailyAction->setChecked(schedule == DAILY);
            weeklyAction->setChecked(schedule == WEEKLY);
            monthlyAction->setChecked(schedule == MONTHLY);
            disableAction->setChecked(schedule == DISABLED);
        };

        refreshCheck();

        QObject::connect(everyRunAction, &QAction::triggered, everyRunAction, [=](){
            setSchedule(EVERYRUN);
            refreshCheck();
        });

        QObject::connect(dailyAction, &QAction::triggered, dailyAction, [=](){
            setSchedule(DAILY);
            refreshCheck();
        });

        QObject::connect(weeklyAction, &QAction::triggered, weeklyAction, [=](){
            setSchedule(WEEKLY);
            refreshCheck();
        });

        QObject::connect(monthlyAction, &QAction::triggered, monthlyAction, [=](){
            setSchedule(MONTHLY);
            refreshCheck();
        });

        QObject::connect(disableAction, &QAction::triggered, disableAction, [=](){
            setSchedule(DISABLED);
            refreshCheck();
        });
        return menu;
    }

    QDialog* getUpdateAvailableDialog(const QVersionNumber& newVersion,
                                      const QString& msgBody,
                                      const QUrl& updateUrl){
        auto dialog = new ShowHTMLDialog;
        dialog->setTitle(QCoreApplication::translate("UpdateChecker", "Update available"));
        dialog->setLabel(QCoreApplication::translate("UpdateChecker", "New version \"%1\" of \"%2\" is available. "
                                                                      "Currently you are at \"%3\".\n"
                                                                      "Open download page?")
                         .arg(newVersion.toString(), qApp->applicationName(), qApp->applicationVersion())
                         );
        dialog->setMarkdown(msgBody);
        dialog->setStandardButtons(QDialogButtonBox::Yes | QDialogButtonBox::No);
        dialog->setWindowModality(Qt::ApplicationModal);
        QObject::connect(dialog, &QDialog::accepted, [=](){
            QDesktopServices::openUrl(updateUrl);
        });
        QObject::connect(dialog, &QDialog::finished, dialog, [dialog](){
            dialog->deleteLater();
        });
        return dialog;
    };

    void triggerScheduledCheck(Checker* checker)
    {
        QSettings settings;
        auto lastChecked = settings.value("updateLastChecked").toDateTime();
        auto durationDays = lastChecked.daysTo(QDateTime::currentDateTime());
        bool shouldCheck = false;
        switch (getSchedule())
        {
            case EVERYRUN: shouldCheck = true; break;
            case DAILY: shouldCheck = durationDays >= 1; break;
            case WEEKLY: shouldCheck = durationDays >= 7; break;
            case MONTHLY: shouldCheck = durationDays >= 30; break;
            case DISABLED: shouldCheck = false; break;
        }
        if (shouldCheck)
        {
            // To keep one responding on signal emitting,
            // we just disconnect all slots when operation done.
            QObject::connect(checker, &Checker::updateAvailable, checker, [checker](
                             const QVersionNumber& newVersion,
                             const QString& msgBody,
                             const QUrl& updateUrl){
                auto dialog = getUpdateAvailableDialog(newVersion, msgBody, updateUrl);
                dialog->show();
                checker->disconnect();
            });
            QObject::connect(checker, &Checker::alreadyUpToDate, checker, [checker](){
                //No need to notify user already up-to-date when auto checking
                checker->disconnect();
            });
            QObject::connect(checker, &Checker::errorOccurred, checker, [checker](const QString& msg){
                qWarning("[Update checker] error when checking, %s", msg.toStdString().c_str());
                checker->disconnect();
            });
            checker->triggerUpdateCheck();
        }
    }

    void checkManully(Checker* checker)
    {
        // To keep one responding on signal emitting,
        // we just disconnect all slots when operation done.
        QObject::connect(checker, &Checker::updateAvailable, checker, [checker](
                         const QVersionNumber& newVersion,
                         const QString& msgBody,
                         const QUrl& updateUrl){
            auto dialog = getUpdateAvailableDialog(newVersion, msgBody, updateUrl);
            dialog->show();
            checker->disconnect();
        });
        QObject::connect(checker, &Checker::alreadyUpToDate, checker, [checker](){
            QMessageBox::information(nullptr, {},
                                     QCoreApplication::translate("UpdateChecker", "You are already up-to-date."));
            checker->disconnect();
        });
        QObject::connect(checker, &Checker::errorOccurred, checker, [checker](const QString& msg){
            QMessageBox::warning(nullptr, {},
                                 QCoreApplication::translate("UpdateChecker", "Error occurred when checking update: %1").arg(msg));
            qWarning("[Update checker] error when checking, %s", msg.toStdString().c_str());
            checker->disconnect();
        });
        checker->triggerUpdateCheck();
    }

}

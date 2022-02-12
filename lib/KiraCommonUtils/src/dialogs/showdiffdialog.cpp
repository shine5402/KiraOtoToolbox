#include <kira/dialogs/showdiffdialog.h>
#include "kira/darkmode.h"
#include "ui_showdiffdialog.h"
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include "../../lib/diff-match-patch/diff_match_patch.h"
#include <QMessageBox>

ShowDiffDialog::ShowDiffDialog(QString source, QString result, const QString& title,
                               const QString& message, QDialogButtonBox::StandardButtons standardButtons,
                               QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowDiffDialog),
    source(std::move(source)), result(std::move(result))
{
    ui->setupUi(this);

    setMessage(message);
    setStandardButtons(standardButtons);
    setWindowTitle(title);

    ui->sourceTextEdit->setPlainText(this->source);
    ui->resultTextEdit->setPlainText(this->result);
}

void ShowDiffDialog::setMessage(const QString& message)
{
    if (!message.isEmpty()){
        ui->messageLabel->setVisible(true);
        ui->messageLabel->setText(message);
    }
    else
        ui->messageLabel->setVisible(false);
}

void ShowDiffDialog::setStandardButtons(QDialogButtonBox::StandardButtons buttons)
{
    ui->buttonBox->setStandardButtons(buttons);
}

void ShowDiffDialog::open()
{
    startDiffCalc();
    QDialog::open();
}

int ShowDiffDialog::exec()
{
    startDiffCalc();
    return QDialog::exec();
}

void ShowDiffDialog::startDiffCalc()
{
    if (source.isEmpty() || result.isEmpty()){
        ui->diffTextEdit->setText(tr("Either source or result is empty. No need for diff."));
        return;
    }
    if (source == result){
        ui->diffTextEdit->setText(tr("Source and result is same. No need for diff."));
        return;
    }

    auto future = QtConcurrent::run([&]() -> QString { //returns diff's prettyHtml
        diff_match_patch dmp;
        //TODO:Use a parameter to determine which mode should be used
        auto diff = dmp.diff_lineMode(source, result, std::numeric_limits<clock_t>::max());
        auto prettyHtml = [](const auto& diffs) -> auto{
            QString html;
            QString text;
            foreach(Diff aDiff, diffs) {
                text = aDiff.text;
                text.replace("&", "&amp;").replace("<", "&lt;")
                        .replace(">", "&gt;").replace("\n", "<br>");
                switch (aDiff.operation) {
                    case INSERT:
                        html += QStringLiteral("<ins style=\"background:%1;text-decoration:underline;\">")
                                .arg(DarkMode::getCurrentMode() == DarkMode::LIGHT ? "#e6ffe6" : "#147314")
                                + text
                                + QStringLiteral("</ins>");
                        break;
                    case DELETE:
                        html += QStringLiteral("<del style=\"background:%1;text-decoration:line-through;\">")
                                .arg(DarkMode::getCurrentMode() == DarkMode::LIGHT ? "#ffe6e6" : "#B40000")
                                + text
                                + QStringLiteral("</del>");
                        break;
                    case EQUAL:
                        html += QStringLiteral("<span>") + text + QStringLiteral("</span>");
                        break;
                }
            }
            return html;
        };
        return prettyHtml(diff);
    });
    futureSynchronizer.addFuture(future);

    watcher = new QFutureWatcher<QString>(this);
    connect(watcher, &QFutureWatcher<QString>::finished, this, &ShowDiffDialog::handleDiffCalcFinished);
    watcher->setFuture(future);

    ui->diffProgressLabel->setText(tr("Calculating differences..."));
}

void ShowDiffDialog::handleDiffCalcFinished()
{
    ui->diffProgressLabel->setText(tr("Diff calculation is completed."));
    try {
    ui->diffTextEdit->setHtml(watcher->result());
    }
    catch (std::exception* e){
        QMessageBox::critical(this, {}, tr("Error occured when calculating difference. Error info: %1").arg(e->what()));
        qCritical() << "(Diff Dialog) Exception occured in diff method. what():" << e->what();
    }

    catch (...) {
        QMessageBox::critical(this, {}, tr("Error occured when calculating difference."));
        qCritical() << "(Diff Dialog) Exception occured in diff method.";
    }

    ui->tabWidget->setCurrentIndex(2);//2 for diff tab.
}

ShowDiffDialog::~ShowDiffDialog()
{
    delete ui;
}

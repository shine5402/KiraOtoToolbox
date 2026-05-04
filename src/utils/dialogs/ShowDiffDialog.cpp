#include "utils/dialogs/ShowDiffDialog.h"
#include "ui_ShowDiffDialog.h"

#include <QFuture>
#include <QFutureWatcher>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>

#include <dtl/dtl.hpp>

#include <string>
#include <vector>

namespace {

enum Operation { DELETE, INSERT, EQUAL };

struct Diff {
    Operation operation;
    QString text;
};

QList<Diff> computeLineDiff(const QString &source, const QString &result)
{
    const QStringList srcLines = source.split(QChar{u'\n'});
    const QStringList resLines = result.split(QChar{u'\n'});

    std::vector<std::string> srcStrs;
    std::vector<std::string> resStrs;
    srcStrs.reserve(srcLines.size());
    resStrs.reserve(resLines.size());
    for (const auto &line : srcLines)
        srcStrs.push_back(line.toStdString());
    for (const auto &line : resLines)
        resStrs.push_back(line.toStdString());

    dtl::Diff<std::string> d(srcStrs, resStrs);
    d.compose();

    QList<Diff> diffs;
    for (const auto &sesElem : d.getSes().getSequence()) {
        Operation op;
        switch (sesElem.second.type) {
        case dtl::SES_ADD:
            op = INSERT;
            break;
        case dtl::SES_DELETE:
            op = DELETE;
            break;
        default:
            op = EQUAL;
            break;
        }

        QString text = QString::fromStdString(sesElem.first) + QChar{u'\n'};

        if (!diffs.isEmpty() && diffs.last().operation == op) {
            diffs.last().text += text;
        } else {
            diffs.append({op, text});
        }
    }
    return diffs;
}

} // namespace

ShowDiffDialog::ShowDiffDialog(QString source, QString result, const QString &title, const QString &message,
                               QDialogButtonBox::StandardButtons standardButtons, QWidget *parent)
    : QDialog(parent), ui(new Ui::ShowDiffDialog), source(std::move(source)), result(std::move(result))
{
    ui->setupUi(this);

    setMessage(message);
    setStandardButtons(standardButtons);
    setWindowTitle(title);

    ui->sourceTextEdit->setPlainText(this->source);
    ui->resultTextEdit->setPlainText(this->result);
}

void ShowDiffDialog::setMessage(const QString &message)
{
    if (!message.isEmpty()) {
        ui->messageLabel->setVisible(true);
        ui->messageLabel->setText(message);
    } else
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
    if (source.isEmpty() || result.isEmpty()) {
        ui->diffTextEdit->setText(tr("Either source or result is empty. No need for diff."));
        return;
    }
    if (source == result) {
        ui->diffTextEdit->setText(tr("Source and result is same. No need for diff."));
        return;
    }

    bool isLightTheme = palette().color(QPalette::Window).lightness() > 128;
    auto future = QtConcurrent::run([&, isLightTheme]() -> QString { // returns diff's prettyHtml
        auto diff = computeLineDiff(source, result);
        auto prettyHtml = [isLightTheme](const auto &diffs) -> auto {
            QString html;
            QString text;
            foreach (Diff aDiff, diffs) {
                text = aDiff.text;
                text.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;").replace("\n", "<br>");
                switch (aDiff.operation) {
                case INSERT:
                    html += QStringLiteral("<ins style=\"background:%1;text-decoration:underline;\">")
                                .arg(isLightTheme ? "#e6ffe6" : "#147314") +
                            text + QStringLiteral("</ins>");
                    break;
                case DELETE:
                    html += QStringLiteral("<del style=\"background:%1;text-decoration:line-through;\">")
                                .arg(isLightTheme ? "#ffe6e6" : "#B40000") +
                            text + QStringLiteral("</del>");
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
    } catch (std::exception *e) {
        QMessageBox::critical(this, {}, tr("Error occured when calculating difference. Error info: %1").arg(e->what()));
        qCritical() << "(Diff Dialog) Exception occured in diff method. what():" << e->what();
    }

    catch (...)
    {
        QMessageBox::critical(this, {}, tr("Error occured when calculating difference."));
        qCritical() << "(Diff Dialog) Exception occured in diff method.";
    }

    ui->tabWidget->setCurrentIndex(2); // 2 for diff tab.
}

ShowDiffDialog::~ShowDiffDialog()
{
    delete ui;
}

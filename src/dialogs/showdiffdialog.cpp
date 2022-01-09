#include <kira/dialogs/showdiffdialog.h>
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
        auto diff = dmp.diff_lineMode(source, result, std::numeric_limits<clock_t>::max());
        return dmp.diff_prettyHtml(diff);
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

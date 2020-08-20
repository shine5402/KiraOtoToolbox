#include "showdiffdialog.h"
#include "ui_showdiffdialog.h"
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include "../lib/diff-match-patch/diff_match_patch.h"

ShowDiffDialog::ShowDiffDialog(QString source, QString result, const QString& message, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowDiffDialog),
    source(std::move(source)), result(std::move(result))
{
    ui->setupUi(this);
    setMessage(message);

    ui->sourceTextEdit->setText(source);
    ui->resultTextEdit->setText(result);
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
    auto future = QtConcurrent::run([&]() -> QString { //returns diff's prettyHtml
        diff_match_patch dmp;
        dmp.Diff_Timeout = 0.0f;
        auto diff = dmp.diff_main(source, result, true);
        return dmp.diff_prettyHtml(diff);
    });
    futureSynchronizer.addFuture(future);

    watcher = new QFutureWatcher<QString>(this);
    connect(watcher, &QFutureWatcher<QString>::finished, this, &ShowDiffDialog::handleDiffCalcFinished);
    watcher->setFuture(future);

    ui->diffProgressLabel->setText(tr("正在计算差异……"));
}

void ShowDiffDialog::handleDiffCalcFinished()
{
    ui->diffProgressLabel->setText(tr("差异计算完成。"));
    ui->diffTextEdit->setHtml(watcher->result());
    ui->tabWidget->setCurrentIndex(2);//2 for diff tab.
}

ShowDiffDialog::~ShowDiffDialog()
{
    delete ui;
}

#ifndef SHOWDIFFDIALOG_H
#define SHOWDIFFDIALOG_H

#include <QDialog>
#include <QFutureWatcher>
#include <QFutureSynchronizer>
#include <QDialogButtonBox>

namespace Ui {
    class ShowDiffDialog;
}

class ShowDiffDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowDiffDialog(QString source, QString result, const QString& title = {},
                            const QString& message = {},
                            QDialogButtonBox::StandardButtons standardButtons = QDialogButtonBox::Ok,
                            QWidget *parent = nullptr);
    ~ShowDiffDialog();

    void setMessage(const QString& message);
    void setStandardButtons(QDialogButtonBox::StandardButtons buttons);

    void open() override;
    int exec() override;

private:
    Ui::ShowDiffDialog *ui;
    QString source;
    QString result;
    void startDiffCalc();
    QFutureWatcher<QString>* watcher;
    QFutureSynchronizer<QString> futureSynchronizer;
private slots:
    void handleDiffCalcFinished();
};

#endif // SHOWDIFFDIALOG_H

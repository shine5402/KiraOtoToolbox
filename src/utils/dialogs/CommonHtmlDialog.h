#ifndef COMMONHTMLDIALOG_H
#define COMMONHTMLDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>

namespace Ui {
class CommonHtmlDialog;
}

class CommonHtmlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CommonHtmlDialog(QWidget *parent = nullptr);
    ~CommonHtmlDialog();

    void setLabel(const QString &text);
    void setHTML(const QString &html);
    void setMarkdown(const QString &markdown);
    void setStandardButtons(QDialogButtonBox::StandardButtons buttons);
    void setAllowRemoteImageLoad(bool allow);
    void setOpenExternalLinks(bool open);

private:
    Ui::CommonHtmlDialog *ui;
};

#endif // COMMONHTMLDIALOG_H

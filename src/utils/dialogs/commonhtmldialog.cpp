#include "utils/dialogs/commonhtmldialog.h"
#include "ui_commonhtmldialog.h"

CommonHtmlDialog::CommonHtmlDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CommonHtmlDialog)
{
    ui->setupUi(this);
    setLabel({});
}

CommonHtmlDialog::~CommonHtmlDialog()
{
    delete ui;
}

void CommonHtmlDialog::setLabel(const QString &text)
{
    ui->label->setText(text);
    ui->label->setVisible(!text.isEmpty());
}

void CommonHtmlDialog::setHTML(const QString &html)
{
    ui->textBrowser->setHtml(html);
    auto cursor = ui->textBrowser->textCursor();
    cursor.setPosition(0);
    ui->textBrowser->setTextCursor(cursor);
}

void CommonHtmlDialog::setMarkdown(const QString &markdown)
{
    ui->textBrowser->document()->setMarkdown(markdown);
    auto cursor = ui->textBrowser->textCursor();
    cursor.setPosition(0);
    ui->textBrowser->setTextCursor(cursor);
}

void CommonHtmlDialog::setStandardButtons(QDialogButtonBox::StandardButtons buttons)
{
    ui->buttonBox->setStandardButtons(buttons);
}

void CommonHtmlDialog::setAllowRemoteImageLoad(bool allow)
{
    ui->textBrowser->setAllowRemoteImageLoad(allow);
}

void CommonHtmlDialog::setOpenExternalLinks(bool open)
{
    ui->textBrowser->setOpenExternalLinks(open);
}

#include "javascripttooloptionwidget.h"
#include "kira/darkmode.h"
#include "ui_javascripttooloptionwidget.h"
#include <QScrollBar>
#include <QTextStream>
#include <qsourcehighliter.h>
#include <QtDebug>

JavaScriptToolOptionWidget::JavaScriptToolOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::JavaScriptToolOptionWidget)
{
    ui->setupUi(this);

    auto lineNumPalette = ui->lineNumberTextEdit->palette();
    auto lineNumBg = DarkMode::getCurrentMode() == DarkMode::LIGHT ? lineNumPalette.color(QPalette::Base).darker(110) : lineNumPalette.color(QPalette::Base).lighter();
    lineNumPalette.setColor(QPalette::Base, lineNumBg);
    ui->lineNumberTextEdit->setPalette(lineNumPalette);

    auto lineNumVScrollBar = ui->lineNumberTextEdit->verticalScrollBar();
    auto jsVScrollBar = ui->jsTextEdit->verticalScrollBar();
    connect(lineNumVScrollBar, &QScrollBar::valueChanged, jsVScrollBar, &QScrollBar::setValue);
    connect(jsVScrollBar, &QScrollBar::valueChanged, lineNumVScrollBar, &QScrollBar::setValue);

    connect(ui->jsTextEdit, &QPlainTextEdit::textChanged, this, &JavaScriptToolOptionWidget::refillLineNumbers);
    connect(ui->jsTextEdit, &QPlainTextEdit::cursorPositionChanged, this, &JavaScriptToolOptionWidget::syncCursors);

    highlighter = new QSourceHighlite::QSourceHighliter(ui->jsTextEdit->document(), QSourceHighlite::QSourceHighliter::Monokai);
    highlighter->setCurrentLanguage(QSourceHighlite::QSourceHighliter::CodeJs);

    auto font = QFont("Jetbrains Mono");
    font.setStyleHint(QFont::Monospace);
    ui->lineNumberTextEdit->setFont(font);
    ui->jsTextEdit->setFont(font);
    qDebug() << "Actual Monospace font" << QFontInfo(font).family();

    ui->jsTextEdit->setTabStopDistance(ui->jsTextEdit->fontMetrics().horizontalAdvance("    "));//4 space
}

JavaScriptToolOptionWidget::~JavaScriptToolOptionWidget()
{
    delete ui;
}

void JavaScriptToolOptionWidget::refillLineNumbers()
{
    QString content;
    QTextStream stream(&content);
    auto count = ui->jsTextEdit->document()->blockCount();
    for (auto i = 1; i <= count; ++i){
        stream << i;
        if (i < count)
            stream << Qt::endl;
    }
    auto width = ui->lineNumberTextEdit->fontMetrics().horizontalAdvance(QString("%1").arg(count)) + 8;
    ui->lineNumberTextEdit->setFixedWidth(width);
    auto scrollPos = ui->jsTextEdit->verticalScrollBar()->value();
    ui->lineNumberTextEdit->document()->setPlainText(content);
    syncCursors();
    ui->jsTextEdit->verticalScrollBar()->setValue(scrollPos);
}

void JavaScriptToolOptionWidget::syncCursors()
{
    auto cursor = ui->lineNumberTextEdit->textCursor();
    cursor.setPosition(ui->lineNumberTextEdit->document()->findBlockByNumber(
                           ui->jsTextEdit->textCursor().blockNumber()
                           ).position());
    ui->lineNumberTextEdit->setTextCursor(cursor);
}


OptionContainer JavaScriptToolOptionWidget::getOptions() const
{
    OptionContainer options;

    options.setOption("script", ui->jsTextEdit->document()->toPlainText());
    options.setOption("interpretBySystemEncoding", ui->interpretBySystemEncodingCheckBox->isChecked());

    return options;
}

void JavaScriptToolOptionWidget::setOptions(const OptionContainer& options)
{
    ui->jsTextEdit->document()->setPlainText(options.getOption("script").toString());
    syncCursors();
    ui->interpretBySystemEncodingCheckBox->setChecked(options.getOption("interpretBySystemEncoding").toBool());
}

QJsonObject JavaScriptToolOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject json;

    json.insert("script", options.getOption("script").toString());
    json.insert("interpretBySystemEncoding", options.getOption("interpretBySystemEncoding").toBool());

    return json;
}

OptionContainer JavaScriptToolOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;

    options.setOption("script", json.value("script").toString());
    options.setOption("interpretBySystemEncoding", json.value("interpretBySystemEncoding").toBool());

    return options;
}

int JavaScriptToolOptionWidget::optionJsonVersion() const
{
    return 1;
}

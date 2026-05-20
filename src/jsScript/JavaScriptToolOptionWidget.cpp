#include "JavaScriptToolOptionWidget.h"
#include "ui_JavaScriptToolOptionWidget.h"

#include <QApplication>
#include <QEvent>
#include <QFontInfo>
#include <QJsonObject>
#include <Qsci/qsciapis.h>
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qsciscintilla.h>

JavaScriptToolOptionWidget::JavaScriptToolOptionWidget(QWidget *parent)
    : ToolOptionWidget(parent), ui(new Ui::JavaScriptToolOptionWidget)
{
    ui->setupUi(this);

    auto *sci = ui->jsTextEdit;

    // JavaScript lexer
    auto *lexer = new QsciLexerJavaScript(this);
    sci->setLexer(lexer);

    // Line numbers
    sci->setMarginType(0, QsciScintilla::NumberMargin);
    sci->setMarginWidth(0, "0000");

    // Folding
    sci->setFolding(QsciScintilla::BoxedTreeFoldStyle);

    // Auto-indent and brace matching
    sci->setAutoIndent(true);
    sci->setBraceMatching(QsciScintilla::SloppyBraceMatch);

    // Font
    auto font = QFont("JetBrains Mono");
    font.setStyleHint(QFont::Monospace);
    sci->setFont(font);
    sci->setMarginsFont(font);

    // Tab stops
    sci->setTabWidth(4);

    // Auto-completion
    auto *api = new QsciAPIs(lexer);
    api->load(":/api/javascript.api");
    api->load(":/api/kiraoto_api.api");
    api->prepare();
    sci->setAutoCompletionSource(QsciScintilla::AcsAll);
    sci->setAutoCompletionThreshold(1);
    sci->setAutoCompletionCaseSensitivity(false);
    sci->setAutoCompletionReplaceWord(true);
    sci->setAutoCompletionShowSingle(true);

    applyTheme();

    connect(sci, &QsciScintilla::textChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->interpretBySystemEncodingCheckBox, &QCheckBox::toggled, this, &ToolOptionWidget::userSettingsChanged);
}

void JavaScriptToolOptionWidget::changeEvent(QEvent *event)
{
    ToolOptionWidget::changeEvent(event);
    if (event->type() == QEvent::ApplicationPaletteChange || event->type() == QEvent::PaletteChange)
        applyTheme();
}

void JavaScriptToolOptionWidget::applyTheme()
{
    const auto &appPalette = QApplication::palette();
    const bool dark = appPalette.color(QPalette::Window).lightness() < 128;

    auto *sci = ui->jsTextEdit;

    // Background and foreground
    sci->setPaper(appPalette.color(QPalette::Base));
    sci->setColor(appPalette.color(QPalette::Text));

    // Selection colors
    sci->setSelectionBackgroundColor(appPalette.color(QPalette::Highlight));
    sci->setSelectionForegroundColor(appPalette.color(QPalette::HighlightedText));

    // Caret color
    sci->setCaretForegroundColor(appPalette.color(QPalette::Text));

    // Margin (line number) colors
    sci->setMarginsBackgroundColor(dark ? appPalette.color(QPalette::Base).darker(110)
                                        : appPalette.color(QPalette::Base).lighter(105));
    sci->setMarginsForegroundColor(appPalette.color(QPalette::Mid));
}

JavaScriptToolOptionWidget::~JavaScriptToolOptionWidget()
{
    delete ui;
}

OptionContainer JavaScriptToolOptionWidget::getOptions() const
{
    OptionContainer options;

    options.setOption("script", ui->jsTextEdit->text());
    options.setOption("interpretBySystemEncoding", ui->interpretBySystemEncodingCheckBox->isChecked());

    return options;
}

void JavaScriptToolOptionWidget::setOptions(const OptionContainer &options)
{
    ui->jsTextEdit->setText(options.getOption("script").toString());
    ui->interpretBySystemEncodingCheckBox->setChecked(options.getOption("interpretBySystemEncoding").toBool());
}

QJsonObject JavaScriptToolOptionWidget::optionsToJson(const OptionContainer &options) const
{
    QJsonObject json;

    json.insert("script", options.getOption("script").toString());
    json.insert("interpretBySystemEncoding", options.getOption("interpretBySystemEncoding").toBool());

    return json;
}

OptionContainer JavaScriptToolOptionWidget::jsonToOptions(const QJsonObject &json) const
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

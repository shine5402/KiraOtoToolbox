#include "JavaScriptToolOptionWidget.h"
#include "ui_JavaScriptToolOptionWidget.h"

#include <QApplication>
#include <QEvent>
#include <QFontInfo>
#include <QJsonObject>
#include <Qsci/qsciapis.h>
#include <Qsci/qscilexercpp.h>
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

    // Font — must be set on the *lexer*, not just the scintilla. Once a lexer is
    // attached, its per-style fonts override sci->setFont(). The lexer defaults
    // (esp. comments) fall back to an italic system font on macOS, which looks
    // out of place. setFont(f, -1) iterates every style and overrides them all.
    auto font = QFont("JetBrains Mono");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    lexer->setFont(font);
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
    auto *lexer = qobject_cast<QsciLexerJavaScript *>(sci->lexer());

    const QColor bg = appPalette.color(QPalette::Base);
    const QColor fg = appPalette.color(QPalette::Text);

    // Per-style syntax colors (VS Code-ish palette, readable in both modes).
    const QColor commentColor = dark ? QColor(QStringLiteral("#6A9955")) : QColor(QStringLiteral("#008000"));
    const QColor keywordColor = dark ? QColor(QStringLiteral("#569CD6")) : QColor(QStringLiteral("#0000FF"));
    const QColor numberColor  = dark ? QColor(QStringLiteral("#B5CEA8")) : QColor(QStringLiteral("#098658"));
    const QColor stringColor  = dark ? QColor(QStringLiteral("#CE9178")) : QColor(QStringLiteral("#A31515"));

    // With a lexer attached, sci->setColor/setPaper only hit STYLE_DEFAULT; the
    // lexer's per-style colors override it. The lexer defaults assume a white
    // background, so on dark mode keywords/strings render in unreadable light
    // colors. Push bg + base fg through every lexer style, then override the
    // token styles that benefit from color.
    if (lexer) {
        lexer->setPaper(bg);
        lexer->setColor(fg);
        lexer->setColor(commentColor, QsciLexerCPP::Comment);
        lexer->setColor(commentColor, QsciLexerCPP::CommentLine);
        lexer->setColor(commentColor, QsciLexerCPP::CommentDoc);
        lexer->setColor(keywordColor, QsciLexerCPP::Keyword);
        lexer->setColor(numberColor, QsciLexerCPP::Number);
        lexer->setColor(stringColor, QsciLexerCPP::DoubleQuotedString);
        lexer->setColor(stringColor, QsciLexerCPP::SingleQuotedString);
    }

    // Scintilla-level defaults (cover non-lexer areas and the base style).
    sci->setPaper(bg);
    sci->setColor(fg);

    // Selection colors
    sci->setSelectionBackgroundColor(appPalette.color(QPalette::Highlight));
    sci->setSelectionForegroundColor(appPalette.color(QPalette::HighlightedText));

    // Caret color
    sci->setCaretForegroundColor(fg);

    // Margin (line number) colors. Mix fg/bg so the line number is a mid-grey
    // that stays readable on either theme — QPalette::Mid is near-black on the
    // macOS dark palette and renders the numbers invisible.
    const QColor lineNumberColor = QColor(
        (fg.red() + bg.red()) / 2,
        (fg.green() + bg.green()) / 2,
        (fg.blue() + bg.blue()) / 2);
    sci->setMarginsBackgroundColor(dark ? bg.darker(110) : bg.lighter(105));
    sci->setMarginsForegroundColor(lineNumberColor);

    // Fold margin: its background defaults to a light grey that shows up as a
    // wide separator strip between line numbers and code. Blend it with the code
    // background; keep the fold-marker foreground visible via Mid.
    sci->setFoldMarginColors(appPalette.color(QPalette::Mid), bg);
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

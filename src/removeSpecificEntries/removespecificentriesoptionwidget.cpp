#include "removespecificentriesoptionwidget.h"
#include "ui_removespecificentriesoptionwidget.h"

RemoveSpecificEntriesOptionWidget::RemoveSpecificEntriesOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::RemoveSpecificEntriesOptionWidget)
{
    ui->setupUi(this);

    connect(ui->buttonGroup, &QButtonGroup::idToggled, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->patternLineEdit, &QLineEdit::textEdited, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->caseSensitiveCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
}

RemoveSpecificEntriesOptionWidget::~RemoveSpecificEntriesOptionWidget()
{
    delete ui;
}

OptionContainer RemoveSpecificEntriesOptionWidget::getOptions() const
{
    OptionContainer options;

    MatchStrategy matchStrategy = Exact;
    if (ui->exactRadioButton->isChecked())
        matchStrategy = Exact;
    if (ui->partialRadioButton->isChecked())
        matchStrategy = Partial;
    if (ui->regexRadioButton->isChecked())
        matchStrategy = Regex;

    options.setOption("matchStrategy", matchStrategy);
    options.setOption("pattern", ui->patternLineEdit->text());
    options.setOption("caseSensitive", ui->caseSensitiveCheckBox->isChecked());

    return options;
}

void RemoveSpecificEntriesOptionWidget::setOptions(const OptionContainer& options)
{
    auto matchStrategy = (MatchStrategy) options.getOption("matchStrategy", Exact).toInt();
    switch (matchStrategy){
    case Exact:ui->exactRadioButton->setChecked(true);break;
    case Partial:ui->partialRadioButton->setChecked(true);break;
    case Regex:ui->regexRadioButton->setChecked(true);break;
    }

    ui->patternLineEdit->setText(options.getOption("pattern").toString());
    ui->caseSensitiveCheckBox->setChecked(options.getOption("caseSensitive").toBool());
}

QJsonObject RemoveSpecificEntriesOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject json;

    json.insert("matchStrategy", options.getOption("matchStrategy").toInt());
    json.insert("pattern", options.getOption("pattern").toString());
    json.insert("caseSensitive", options.getOption("caseSensitive").toBool());

    return json;
}

OptionContainer RemoveSpecificEntriesOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;

    options.setOption("matchStrategy", json.value("matchStrategy").toInt());
    options.setOption("pattern", options.getOption("pattern").toString());
    options.setOption("caseSensitive", options.getOption("caseSensitive").toBool());

    return options;
}

int RemoveSpecificEntriesOptionWidget::optionJsonVersion() const
{
    return 1;
}

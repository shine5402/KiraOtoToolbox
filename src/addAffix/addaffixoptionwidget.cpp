#include "addaffixoptionwidget.h"
#include <QFormLayout>

AddAffixOptionWidget::AddAffixOptionWidget(QWidget *parent) : ToolOptionWidget(parent)
{
    prefixEdit = new QLineEdit(this);
    suffixEdit = new QLineEdit(this);
    auto layout = new QFormLayout(this);
    layout->addRow(tr("Prefix: "), prefixEdit);
    layout->addRow(tr("Suffix: "), suffixEdit);
    setLayout(layout);

    connect(prefixEdit, &QLineEdit::textEdited, this, &ToolOptionWidget::userSettingsChanged);
    connect(suffixEdit, &QLineEdit::textEdited, this, &ToolOptionWidget::userSettingsChanged);
}

OptionContainer AddAffixOptionWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("prefix", prefixEdit->text());
    options.setOption("suffix", suffixEdit->text());
    return options;
}

void AddAffixOptionWidget::setOptions(const OptionContainer& options)
{
    prefixEdit->setText(options.getOption("prefix").toString());
    suffixEdit->setText(options.getOption("suffix").toString());
}



QJsonObject AddAffixOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject jsonObj;

    jsonObj.insert("prefix", options.getOption("prefix").toString());
    jsonObj.insert("suffix", options.getOption("suffix").toString());

    return jsonObj;
}

OptionContainer AddAffixOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;
    options.setOption("prefix", json.value("prefix"));
    options.getOption("suffix", json.value("suffix"));
    return options;
}


int AddAffixOptionWidget::optionJsonVersion() const
{
    return 1;
}

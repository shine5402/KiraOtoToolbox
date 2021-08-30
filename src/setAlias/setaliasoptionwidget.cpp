#include "setaliasoptionwidget.h"
#include "ui_setaliasoptionwidget.h"

SetAliasOptionWidget::SetAliasOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::SetAliasOptionWidget)
{
    ui->setupUi(this);
}

SetAliasOptionWidget::~SetAliasOptionWidget()
{
    delete ui;
}


OptionContainer SetAliasOptionWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("renamingRule", ui->ruleLineEdit->text());
    options.setOption("cutHeadCount", ui->headCutSpinBox->value());
    options.setOption("cutTailCount", ui->tailCutSpinBox->value());
    options.setOption("strShouldRemove", ui->removeStrLineEdit->text());
    options.setOption("strShouldRemoveIsRegex", ui->removeStrRegexCheckBox->isChecked());
    options.setOption("onlyForEmpty", ui->emptyOnlyCheckBox->isChecked());
    return options;
}

void SetAliasOptionWidget::setOptions(const OptionContainer& options)
{
    ui->ruleLineEdit->setText(options.getOption("renamingRule").toString());
    ui->headCutSpinBox->setValue(options.getOption("cutHeadCount").toInt());
    ui->tailCutSpinBox->setValue(options.getOption("cutTailCount").toInt());
    ui->removeStrLineEdit->setText(options.getOption("strShouldRemove").toString());
    ui->removeStrRegexCheckBox->setChecked(options.getOption("strShouldRemoveIsRegex").toBool());
    ui->emptyOnlyCheckBox->setChecked(options.getOption("onlyForEmpty").toBool());
}


QJsonObject SetAliasOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject jsonObj;
    jsonObj.insert("renamingRule", options.getOption("renamingRule").toString());
    jsonObj.insert("cutHeadCount", options.getOption("cutHeadCount").toInt());
    jsonObj.insert("cutTailCount", options.getOption("cutTailCount").toInt());
    jsonObj.insert("strShouldRemove", options.getOption("strShouldRemove").toString());
    jsonObj.insert("strShouldRemoveIsRegex", options.getOption("strShouldRemoveIsRegex").toBool());
    jsonObj.insert("onlyForEmpty", options.getOption("onlyForEmpty").toBool());
    return jsonObj;
}

OptionContainer SetAliasOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;
    options.setOption("renamingRule", json.value("renamingRule").toString());
    options.setOption("cutHeadCount", json.value("cutHeadCount").toInt());
    options.setOption("cutTailCount", json.value("cutTailCount").toInt());
    options.setOption("strShouldRemove", json.value("strShouldRemove").toString());
    options.setOption("strShouldRemoveIsRegex", json.value("strShouldRemoveIsRegex").toBool());
    options.setOption("onlyForEmpty", json.value("onlyForEmpty").toBool());
    return options;
}

int SetAliasOptionWidget::optionJsonVersion() const
{
    return 1;
}

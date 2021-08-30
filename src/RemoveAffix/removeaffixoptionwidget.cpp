#include "removeaffixoptionwidget.h"
#include "ui_removeaffixoptionwidget.h"
#include "utils/widgets/atleastonecheckedbuttongroup.h"
#include <otoentry.h>
#include <QJsonArray>
#include <utils/misc/fplusAdapter.h>

RemoveAffixOptionWidget::RemoveAffixOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::RemoveAffixOptionWidget)
{
    ui->setupUi(this);
    auto group = new AtLeastOneCheckedButtonGroup(this);
    group->addButton(ui->pitchPrefixCheckBox);
    group->addButton(ui->pitchSuffixCheckBox);
}

RemoveAffixOptionWidget::~RemoveAffixOptionWidget()
{
    delete ui;
}

OptionContainer RemoveAffixOptionWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("removePrefix", ui->specificPrefixCheckBox->isChecked());
    options.setOption("prefixList", ui->prefixListWidget->getData());

    options.setOption("removeSuffix", ui->specificSuffixCheckBox->isChecked());
    options.setOption("suffixList", ui->suffixListWidget->getData());

    options.setOption("removePitchAffix", ui->ignorePitchSuffixCheckBox->isChecked());
    options.setOption("removePitchPrefix", ui->pitchPrefixCheckBox->isChecked());
    options.setOption("removePitchSuffix", ui->pitchSuffixCheckBox->isChecked());

    options.setOption("bottomPitch", QString("%1%2").arg(ui->bottomPitchComboBox->currentText()).arg(ui->bottomPitchSpinBox->value()));
    options.setOption("topPitch", QString("%1%2").arg(ui->topPitchComboBox->currentText()).arg(ui->topPitchSpinBox->value()));
    options.setOption("pitchCaseSensitive",ui->pitchCaseSensitiveCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
    options.setOption("pitchCase", ui->pitchCaseComboBox->currentIndex() == 0 ? OtoEntryFunctions::Upper : OtoEntryFunctions::Lower);

    return options;
}

void RemoveAffixOptionWidget::setOptions(const OptionContainer& options)
{
    ui->specificPrefixCheckBox->setChecked(options.getOption("removePrefix").toBool());
    ui->prefixListWidget->setData(options.getOption("prefixList").toStringList());

    ui->specificSuffixCheckBox->setChecked(options.getOption("removeSuffix").toBool());
    ui->suffixListWidget->setData(options.getOption("suffixList").toStringList());

    ui->ignorePitchSuffixCheckBox->setChecked(options.getOption("removePitchAffix").toBool());
    ui->pitchPrefixCheckBox->setChecked(options.getOption("removePitchPrefix").toBool());
    ui->pitchSuffixCheckBox->setChecked(options.getOption("removePitchSuffix", true).toBool());

    auto bottomPitch = options.getOption("bottomPitch", "C1").toString();
    auto topPitch = options.getOption("topPitch", "C7").toString();

    ui->bottomPitchComboBox->setCurrentText(bottomPitch.at(0));
    ui->bottomPitchSpinBox->setValue(bottomPitch.midRef(1,1).toInt());
    ui->topPitchComboBox->setCurrentText(topPitch.at(0));
    ui->topPitchSpinBox->setValue(topPitch.midRef(1,1).toInt());

    ui->pitchCaseSensitiveCheckBox->setChecked(options.getOption("pitchCaseSensitive").value<Qt::CaseSensitivity>() == Qt::CaseSensitive  ? true : false);
    ui->pitchCaseComboBox->setCurrentIndex(options.getOption("pitchCase").toInt());
}

QJsonObject RemoveAffixOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject jsonObj;
    jsonObj.insert("removePrefix", options.getOption("removePrefix").toBool());
    jsonObj.insert("prefixList", QJsonArray::fromStringList(options.getOption("prefixList").toStringList()));
    jsonObj.insert("removeSuffix", options.getOption("removeSuffix").toBool());
    jsonObj.insert("suffixList", QJsonArray::fromStringList(options.getOption("suffixList").toStringList()));
    jsonObj.insert("removePitchAffix", options.getOption("removePitchAffix").toBool());
    jsonObj.insert("removePitchPrefix", options.getOption("removePitchPrefix").toBool());
    jsonObj.insert("removePitchSuffix", options.getOption("removePitchSuffix").toBool());
    jsonObj.insert("bottomPitch", options.getOption("bottomPitch").toString());
    jsonObj.insert("topPitch", options.getOption("topPitch").toString());
    jsonObj.insert("pitchCaseSensitive", options.getOption("pitchCaseSensitive").value<Qt::CaseSensitivity>());
    jsonObj.insert("pitchCase", options.getOption("pitchCase").toInt());
    return jsonObj;
}

OptionContainer RemoveAffixOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;
    options.setOption("removePrefix", json.value("removePrefix").toBool());
    options.setOption("prefixList", getStringListFromJSONObject(json, "prefixList"));
    options.setOption("removeSuffix", json.value("removeSuffix").toBool());
    options.setOption("suffixList", getStringListFromJSONObject(json, "suffixList"));
    options.setOption("removePitchAffix", json.value("removePitchAffix").toBool());
    options.setOption("removePitchPrefix", json.value("removePitchPrefix").toBool());
    options.setOption("removePitchSuffix", json.value("removePitchSuffix").toBool());
    options.setOption("bottomPitch", json.value("bottomPitch").toString());
    options.setOption("topPitch", json.value("topPitch").toString());
    options.setOption("pitchCaseSensitive", json.value("pitchCaseSensitive").toInt());
    options.setOption("pitchCase", json.value("pitchCase").toInt());
    return options;
}

int RemoveAffixOptionWidget::optionJsonVersion() const
{
    return 1;
}

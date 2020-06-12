#include "removeduplicatedialogoptionwidget.h"
#include "ui_removeduplicatedialogoptionwidget.h"

RemoveDuplicateDialogOptionWidget::RemoveDuplicateDialogOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::RemoveDuplicateDialogOptionWidget)
{
    ui->setupUi(this);
}

RemoveDuplicateDialogOptionWidget::~RemoveDuplicateDialogOptionWidget()
{
    delete ui;
}

ToolOptions* RemoveDuplicateDialogOptionWidget::getOptions(QObject* parent) const
{
    auto options = new RemoveDuplicateOptions(parent);

    options->ignoreSpecificSuffix = ui->ignoreSpecificSuffixCheckBox->isChecked();
    options->suffixList = ui->suffixListWidget->getData();
    options->ignorePitchSuffix = ui->ignorePitchSuffixCheckBox->isChecked();
    options->bottomPitch = QString("%1%2").arg(ui->bottomPitchComboBox->currentText()).arg(ui->bottomPitchSpinBox->value());
    options->topPitch = QString("%1%2").arg(ui->topPitchComboBox->currentText()).arg(ui->topPitchSpinBox->value());
    options->pitchCaseSensitive = ui->caseSensitiveCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    options->pitchCase = ui->caseComboBox->currentIndex() == 0 ? OtoEntryFunctions::Upper : OtoEntryFunctions::Lower;
    options->maxDuplicateCount = ui->maxSpinBox->value();
    options->shouldOrganize = ui->organizeCheckBox->isChecked();
    options->organizeStartFrom1 = ui->organizeStartFrom1CheckBox->isChecked();
    options->pitchCaseOrganized = ui->organizeCaseComboBox->currentIndex() == 0 ? OtoEntryFunctions::Upper : OtoEntryFunctions::Lower;

    return options;
}

void RemoveDuplicateDialogOptionWidget::setOptions(const ToolOptions* options)
{
    auto specificOptions = qobject_cast<const RemoveDuplicateOptions*>(options);
    if (!specificOptions)
        return;
    ui->ignoreSpecificSuffixCheckBox->setChecked(specificOptions->ignoreSpecificSuffix);
    ui->suffixListWidget->setData(specificOptions->suffixList);
    ui->ignorePitchSuffixCheckBox->setChecked(specificOptions->ignorePitchSuffix);
    ui->bottomPitchComboBox->setCurrentText(specificOptions->bottomPitch.at(0));
    ui->bottomPitchSpinBox->setValue(specificOptions->bottomPitch.midRef(1,1).toInt());
    ui->topPitchComboBox->setCurrentText(specificOptions->topPitch.at(0));
    ui->topPitchSpinBox->setValue(specificOptions->topPitch.midRef(1,1).toInt());
    ui->caseSensitiveCheckBox->setChecked(specificOptions->pitchCaseSensitive == Qt::CaseSensitive);
    ui->caseComboBox->setCurrentIndex(specificOptions->pitchCase == OtoEntryFunctions::Upper ? 0 : 1);
    ui->maxSpinBox->setValue(specificOptions->maxDuplicateCount);
    ui->organizeCheckBox->setChecked(specificOptions->shouldOrganize);
    ui->organizeStartFrom1CheckBox->setChecked(specificOptions->organizeStartFrom1);
    ui->organizeCaseComboBox->setCurrentIndex(specificOptions->pitchCaseOrganized == OtoEntryFunctions::Upper ? 0 : 1);
}

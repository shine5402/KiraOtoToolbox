#include "removeaffixoptionwidget.h"
#include "ui_removeaffixoptionwidget.h"
#include "utils/widgets/atleastonecheckedbuttongroup.h"
#include <otoentry.h>

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

ToolOptions* RemoveAffixOptionWidget::getOptions(QObject* parent) const
{
    auto options = new ToolOptions(parent);
    options->setOption("removePrefix", ui->specificPrefixCheckBox->isChecked());
    options->setOption("prefixList", ui->prefixListWidget->getData());

    options->setOption("removeSuffix", ui->specificSuffixCheckBox->isChecked());
    options->setOption("suffixList", ui->suffixListWidget->getData());

    options->setOption("removePitchAffix", ui->ignorePitchSuffixCheckBox->isChecked());
    options->setOption("removePitchPrefix", ui->pitchPrefixCheckBox->isChecked());
    options->setOption("removePitchSuffix", ui->pitchSuffixCheckBox->isChecked());

    options->setOption("bottomPitch", QString("%1%2").arg(ui->bottomPitchComboBox->currentText()).arg(ui->bottomPitchSpinBox->value()));
    options->setOption("topPitch", QString("%1%2").arg(ui->topPitchComboBox->currentText()).arg(ui->topPitchSpinBox->value()));
    options->setOption("pitchCaseSensitive",ui->pitchCaseSensitiveCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
    options->setOption("pitchCase", static_cast<int>(ui->pitchCaseComboBox->currentIndex() == 0 ? OtoEntryFunctions::Upper : OtoEntryFunctions::Lower));

    return options;
}

void RemoveAffixOptionWidget::setOptions(const ToolOptions* options)
{
    ui->specificPrefixCheckBox->setChecked(options->getOption("removePrefix").toBool());
    ui->prefixListWidget->setData(options->getOption("prefixList").toStringList());

    ui->specificSuffixCheckBox->setChecked(options->getOption("removeSuffix").toBool());
    ui->suffixListWidget->setData(options->getOption("suffixList").toStringList());

    ui->ignorePitchSuffixCheckBox->setChecked(options->getOption("removePitchAffix").toBool());
    ui->pitchPrefixCheckBox->setChecked(options->getOption("removePitchPrefix").toBool());
    ui->pitchSuffixCheckBox->setChecked(options->getOption("removePitchSuffix").toBool());

    auto bottomPitch = options->getOption("bottomPitch", "C1").toString();
    auto topPitch = options->getOption("topPitch", "C7").toString();

    ui->bottomPitchComboBox->setCurrentText(bottomPitch.at(0));
    ui->bottomPitchSpinBox->setValue(bottomPitch.midRef(1,1).toInt());
    ui->topPitchComboBox->setCurrentText(topPitch.at(0));
    ui->topPitchSpinBox->setValue(topPitch.midRef(1,1).toInt());

    ui->pitchCaseSensitiveCheckBox->setChecked(options->getOption("pitchCaseSensitive").value<Qt::CaseSensitivity>() == Qt::CaseSensitive  ? true : false);
    ui->pitchCaseComboBox->setCurrentIndex(options->getOption("pitchCase").toInt());
}


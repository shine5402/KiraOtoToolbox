#include "CVVCPartSplitOptionWidget.h"
#include "ui_CVVCPartSplitOptionWidget.h"

#include <QJsonArray>

#include "utils/lib_helper/FPlusQtAdapter.h"

CVVCPartSplitOptionWidget::CVVCPartSplitOptionWidget(QWidget *parent)
    : ToolOptionWidget(parent), ui(new Ui::CVVCPartSplitOptionWidget)
{
    ui->setupUi(this);

    connect(ui->seeBeginPatternAsCVCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->seeBeginPatternAsCVContentWidget, &StringListModifyWidget::dataModified, this,
            &ToolOptionWidget::userSettingsChanged);
    connect(ui->seeEndPatternAsCVCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->seeEndPatternAsCVContentWidget, &StringListModifyWidget::dataModified, this,
            &ToolOptionWidget::userSettingsChanged);
    connect(ui->copyCVtoStartOtoCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
}

CVVCPartSplitOptionWidget::~CVVCPartSplitOptionWidget()
{
    delete ui;
}

OptionContainer CVVCPartSplitOptionWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("isSeeBeginPatternAsCV", ui->seeBeginPatternAsCVCheckBox->isChecked());
    options.setOption("seeBeginPatternAsCVContent", ui->seeBeginPatternAsCVContentWidget->getData());
    options.setOption("isSeeEndPatternAsCV", ui->seeEndPatternAsCVCheckBox->isChecked());
    options.setOption("seeEndPatternAsCVContent", ui->seeEndPatternAsCVContentWidget->getData());
    options.setOption("copyCVtoStartOto", ui->copyCVtoStartOtoCheckBox->isChecked());
    return options;
}

void CVVCPartSplitOptionWidget::setOptions(const OptionContainer &options)
{
    ui->seeBeginPatternAsCVCheckBox->setChecked(options.getOption("isSeeBeginPatternAsCV").toBool());
    ui->seeBeginPatternAsCVContentWidget->setData(options.getOption("seeBeginPatternAsCVContent").toStringList());
    ui->seeEndPatternAsCVCheckBox->setChecked(options.getOption("isSeeEndPatternAsCV").toBool());
    ui->seeEndPatternAsCVContentWidget->setData(options.getOption("seeEndPatternAsCVContent").toStringList());
    ui->copyCVtoStartOtoCheckBox->setChecked(options.getOption("copyCVtoStartOto").toBool());
}

QJsonObject CVVCPartSplitOptionWidget::optionsToJson(const OptionContainer &options) const
{
    QJsonObject jsonObj;
    jsonObj.insert("isSeeBeginPatternAsCV", options.getOption("isSeeBeginPatternAsCV").toBool());
    jsonObj.insert("seeBeginPatternAsCVContent",
                   QJsonArray::fromStringList(options.getOption("seeBeginPatternAsCVContent").toStringList()));
    jsonObj.insert("isSeeEndPatternAsCV", options.getOption("isSeeEndPatternAsCV").toBool());
    jsonObj.insert("seeEndPatternAsCVContent",
                   QJsonArray::fromStringList(options.getOption("seeEndPatternAsCVContent").toStringList()));
    jsonObj.insert("copyCVtoStartOto", options.getOption("copyCVtoStartOto").toBool());
    return jsonObj;
}

OptionContainer CVVCPartSplitOptionWidget::jsonToOptions(const QJsonObject &json) const
{
    OptionContainer options;
    options.setOption("isSeeBeginPatternAsCV", json.value("isSeeBeginPatternAsCV").toBool());
    options.setOption("seeBeginPatternAsCVContent", getStringListFromJSONObject(json, "seeBeginPatternAsCVContent"));
    options.setOption("isSeeEndPatternAsCV", json.value("isSeeEndPatternAsCV").toBool());
    options.setOption("seeEndPatternAsCVContent", getStringListFromJSONObject(json, "seeEndPatternAsCVContent"));
    options.setOption("copyCVtoStartOto", json.value("copyCVtoStartOto").toBool());
    return options;
}

int CVVCPartSplitOptionWidget::optionJsonVersion() const
{
    return 1;
}

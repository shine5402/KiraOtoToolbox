#include "cv_vcpartsplitoptionwidget.h"
#include "ui_cv_vcpartsplitoptionwidget.h"
#include <QJsonArray>
#include <utils/misc/fplusAdapter.h>

CV_VCPartSplitOptionWidget::CV_VCPartSplitOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::CV_VCPartSplitOptionWidget)
{
    ui->setupUi(this);
}

CV_VCPartSplitOptionWidget::~CV_VCPartSplitOptionWidget()
{
    delete ui;
}

OptionContainer CV_VCPartSplitOptionWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("isSeeBeginPatternAsCV", ui->seeBeginPatternAsCVCheckBox->isChecked());
    options.setOption("seeBeginPatternAsCVContent", ui->seeBeginPatternAsCVContentWidget->getData());
    options.setOption("isSeeEndPatternAsCV", ui->seeEndPatternAsCVCheckBox->isChecked());
    options.setOption("seeEndPatternAsCVContent", ui->seeEndPatternAsCVContentWidget->getData());
    return options;
}

void CV_VCPartSplitOptionWidget::setOptions(const OptionContainer& options)
{
    ui->seeBeginPatternAsCVCheckBox->setChecked(options.getOption("isSeeBeginPatternAsCV", true).toBool());
    ui->seeBeginPatternAsCVContentWidget->setData(options.getOption("seeBeginPatternAsCVContent", QStringList{"-","・"}).toStringList());
    ui->seeEndPatternAsCVCheckBox->setChecked(options.getOption("isSeeEndPatternAsCV", true).toBool());
    ui->seeEndPatternAsCVContentWidget->setData(options.getOption("seeEndPatternAsCVContent", QStringList{"-","L"}).toStringList());
}


QJsonObject CV_VCPartSplitOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject jsonObj;
    jsonObj.insert("isSeeBeginPatternAsCV", options.getOption("isSeeBeginPatternAsCV").toBool());
    jsonObj.insert("seeBeginPatternAsCVContent", QJsonArray::fromStringList(options.getOption("seeBeginPatternAsCVContent").toStringList()));
    jsonObj.insert("isSeeEndPatternAsCV", options.getOption("isSeeEndPatternAsCV").toBool());
    jsonObj.insert("seeEndPatternAsCVContent", QJsonArray::fromStringList(options.getOption("seeEndPatternAsCVContent").toStringList()));
    return jsonObj;
}

OptionContainer CV_VCPartSplitOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;
    options.setOption("isSeeBeginPatternAsCV", json.value("isSeeBeginPatternAsCV").toBool());
    options.setOption("seeBeginPatternAsCVContent", getStringListFromJSONObject(json, "seeBeginPatternAsCVContent"));
    options.setOption("isSeeEndPatternAsCV", json.value("isSeeEndPatternAsCV").toBool());
    options.setOption("seeEndPatternAsCVContent", getStringListFromJSONObject(json, "seeEndPatternAsCVContent"));
    return options;
}

int CV_VCPartSplitOptionWidget::optionJsonVersion() const
{
    return 1;
}

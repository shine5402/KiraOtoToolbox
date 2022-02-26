#include "mergeotooptionwidget.h"
#include "ui_mergeotooptionwidget.h"

MergeOtoOptionWidget::MergeOtoOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::MergeOtoOptionWidget)
{
    ui->setupUi(this);

    connect(ui->otherOtoLoadWidget, &OtoFileLoadWidget::loaded, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->buttonGroup, &QButtonGroup::idToggled, this, &ToolOptionWidget::userSettingsChanged);
}

MergeOtoOptionWidget::~MergeOtoOptionWidget()
{
    delete ui;
}


OptionContainer MergeOtoOptionWidget::getOptions() const
{
    OptionContainer result;

    result.setOption("otherOtoFileName", ui->otherOtoLoadWidget->fileName());
    result.setOption("otherOtoLoaded", ui->otherOtoLoadWidget->isEntryListReaded());
    result.setOption("otherOtoList", QVariant::fromValue(ui->otherOtoLoadWidget->getEntryList()));
    MergeStrategy mergeStrategy = Replace;
    if (ui->replaceButton->isChecked())
        mergeStrategy = Replace;
    else if (ui->skipButton->isChecked())
        mergeStrategy = Skip;
    else if (ui->keepAllButton->isChecked())
        mergeStrategy = KeepAll;
    result.setOption("mergeStrategy", mergeStrategy);

    return result;
}

void MergeOtoOptionWidget::setOptions(const OptionContainer& options)
{
    ui->otherOtoLoadWidget->reset();
    auto otherOtoLoaded = options.getOption("otherOtoLoaded").toBool();
    if (otherOtoLoaded){
        auto otherOtoFileName = options.getOption("otherOtoFileName").toString();
        auto otherOtoList = options.getOption("otherOtoList").value<OtoEntryList>();
        ui->otherOtoLoadWidget->pretendLoaded(otherOtoFileName, otherOtoList);
    }
    auto mergeStrtegy = (MergeStrategy) options.getOption("mergeStrategy", Replace).toInt();

    switch (mergeStrtegy){
    case Replace: ui->replaceButton->setChecked(true);break;
    case Skip: ui->skipButton->setChecked(true);break;
    case KeepAll: ui->keepAllButton->setChecked(true);break;
    default: Q_UNREACHABLE();
    }
}

QJsonObject MergeOtoOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject jsonObj;
    auto mergeStrtegy = (MergeStrategy) options.getOption("mergeStrategy", Replace).toInt();
    jsonObj.insert("mergeStrtegy", mergeStrtegy);
    return jsonObj;
}

OptionContainer MergeOtoOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer result;
    auto mergeStrtegy = (MergeStrategy) json.value("mergeStrategy").toInt(Replace);
    result.setOption("mergeStrtegy", mergeStrtegy);
    return result;
}

int MergeOtoOptionWidget::optionJsonVersion() const
{
    return 1;
}

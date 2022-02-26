#include "chaininvaliddialogadapter.h"
#include "../notdoanything/notdoanythingotolistmodifyworker.h"
#include <QLabel>

ChainInvalidDialogAdapter::ChainInvalidDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setOptionWidgetMetaObj(ChainInvalidOptionWidget::staticMetaObject);
    setWorkerMetaObj(NotDoAnythingOtoListModifyWorker::staticMetaObject);
}

QString ChainInvalidDialogAdapter::getToolName() const
{
    return tr("Unknown tool");
}

ChainInvalidOptionWidget::ChainInvalidOptionWidget(QWidget* parent) : ToolOptionWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    auto label = new QLabel(this);
    layout->addWidget(label);

    setLayout(layout);
}


OptionContainer ChainInvalidOptionWidget::getOptions() const
{
    OptionContainer options;
    options.setOption("originalClassName", originalClassName);
    options.setOption("options", originalOptionsJson);
    return options;
}

void ChainInvalidOptionWidget::setOptions(const OptionContainer& options)
{
    originalOptionsJson = options.getOption("options").toJsonObject();
    originalClassName = options.getOption("originalClassName").toString();
    label->setText(tr("<p>Unknown tool \"%1\". Please check the version of toolbox that generates this preset "
"or potential typos. </p><p>This step will not take any effect</p>").arg(originalClassName));
}

QJsonObject ChainInvalidOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject jsonObj;
    jsonObj.insert("originalClassName", options.getOption("originalClassName").toString());
    jsonObj.insert("options", originalOptionsJson);
    return jsonObj;
}

OptionContainer ChainInvalidOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;
    options.setOption("originalClassName", json.value("originalClassName").toString());
    options.setOption("options", json.value("options").toObject());
    return options;
}

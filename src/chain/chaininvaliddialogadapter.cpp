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
    return tr("不存在的工具”");
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
    label->setText(tr("<p>程序无法在已知的工具列表中找到“%1”，请确认预设文件对应的工具箱版本和可能的拼写错误。</p><p>该项将不会做任何操作。</p>").arg(originalClassName));
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

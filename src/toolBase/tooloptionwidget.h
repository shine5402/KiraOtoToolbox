#ifndef TOOLOPTIONWIDGET_H
#define TOOLOPTIONWIDGET_H

#include <QWidget>
#include <QVariant>
#include "optioncontainer.h"
#include <QJsonObject>

class ToolOptionWidget : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ToolOptionWidget(QWidget *parent = nullptr);

    virtual OptionContainer getOptions() const;//required
    virtual void setOptions(const OptionContainer& options);//required

    QJsonObject getOptionsJson() const;
    void setOptionsJson(const QJsonObject& json);

    virtual QJsonObject optionsToJson(const OptionContainer& options) const;//required
    virtual OptionContainer jsonToOptions(const QJsonObject& json) const;//required

    virtual int optionJsonVersion() const;//required
    virtual QJsonObject updateOptionJsonFrom(int version, const QJsonObject& json) const;

signals:
    void userSettingsChanged();//required
};

class EmptyToolOptionWidget : public ToolOptionWidget
{
    Q_OBJECT
public:
    explicit EmptyToolOptionWidget(QWidget* parent = nullptr);

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;

    virtual int optionJsonVersion() const override;
    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
};

#include <kira/lib_helper/fplus_qt_adapter.h>
#define getStringListFromJSONObject(jsonObj, key) QStringList(fplus::transform([](QVariant value)->QString{return value.toString();}, jsonObj.value(key).toArray().toVariantList()))

#endif // TOOLOPTIONWIDGET_H

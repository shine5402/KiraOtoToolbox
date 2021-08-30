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

    virtual OptionContainer getOptions() const;
    virtual void setOptions(const OptionContainer& options);

    virtual QJsonObject getOptionsJson() const;
    virtual void setOptionsJson(const QJsonObject& json);

    virtual QJsonObject optionsToJson(const OptionContainer& options) const;
    virtual OptionContainer jsonToOptions(const QJsonObject& json) const;

    virtual int optionJsonVersion() const;
    virtual QJsonObject updateOptionJsonFrom(int version, const QJsonObject& json) const;
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

    QJsonObject getOptionsJson() const override;
    void setOptionsJson(const QJsonObject& json) override;
    virtual int optionJsonVersion() const override;
};

#endif // TOOLOPTIONWIDGET_H

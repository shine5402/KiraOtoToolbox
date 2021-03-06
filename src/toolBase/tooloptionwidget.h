#ifndef TOOLOPTIONWIDGET_H
#define TOOLOPTIONWIDGET_H

#include <QWidget>
#include <QVariant>
#include "optioncontainer.h"

class ToolOptionWidget : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ToolOptionWidget(QWidget *parent = nullptr);

    virtual OptionContainer getOptions() const;
    virtual void setOptions(const OptionContainer& options);
};

class EmptyToolOptionWidget : public ToolOptionWidget
{
    Q_OBJECT
public:
    explicit EmptyToolOptionWidget(QWidget* parent = nullptr);

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const;
    void setOptions(const OptionContainer& options);
};

#endif // TOOLOPTIONWIDGET_H

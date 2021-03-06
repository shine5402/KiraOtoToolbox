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

    virtual OptionContainer getOptions() const = 0;
    virtual void setOptions(const OptionContainer& options) = 0;
};

class EmptyToolOptionWidget : public ToolOptionWidget
{
    Q_OBJECT
public:
    explicit EmptyToolOptionWidget(QWidget* parent = nullptr);
};

#endif // TOOLOPTIONWIDGET_H

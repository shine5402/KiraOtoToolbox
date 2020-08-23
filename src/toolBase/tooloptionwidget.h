#ifndef TOOLOPTIONWIDGET_H
#define TOOLOPTIONWIDGET_H

#include <QWidget>
#include <QVariant>
#include "tooloptions.h"

class ToolOptionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ToolOptionWidget(QWidget *parent = nullptr);

    virtual ToolOptions getOptions() const;
    virtual void setOptions(const ToolOptions& options);
};

class EmptyToolOptionWidget : public ToolOptionWidget
{
    Q_OBJECT
public:
    explicit EmptyToolOptionWidget(QWidget* parent = nullptr);
};

//TODO:空OptionWidget
#endif // TOOLOPTIONWIDGET_H

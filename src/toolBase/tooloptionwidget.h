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

    virtual ToolOptions* getOptions(QObject* parent = nullptr) const;
    virtual void setOptions(const ToolOptions* options);
};

//TODO:空OptionWidget
#endif // TOOLOPTIONWIDGET_H

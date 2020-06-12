#ifndef TOOLOPTIONWIDGET_H
#define TOOLOPTIONWIDGET_H

#include <QWidget>

class ToolOptions : public QObject{
    Q_OBJECT
public:
    explicit ToolOptions(QObject* parent) : QObject(parent){};
};

class ToolOptionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ToolOptionWidget(QWidget *parent = nullptr);

    virtual ToolOptions* getOptions(QObject* parent = nullptr) const = 0;
    virtual void setOptions(const ToolOptions* options) = 0;
};

#endif // TOOLOPTIONWIDGET_H

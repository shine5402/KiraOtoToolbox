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

    virtual ToolOptions* getOptions(QObject* parent = nullptr) const;
    virtual void setOptions(const ToolOptions* options);
};

#endif // TOOLOPTIONWIDGET_H

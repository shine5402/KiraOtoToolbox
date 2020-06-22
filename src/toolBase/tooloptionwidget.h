#ifndef TOOLOPTIONWIDGET_H
#define TOOLOPTIONWIDGET_H

#include <QWidget>
//TODO: getOption/setOption 用QHash<QString, QVariant>存储
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

//TODO:空OptionWidget
#endif // TOOLOPTIONWIDGET_H

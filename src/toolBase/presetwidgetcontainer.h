#ifndef PRESETWIDGETCONTAINER_H
#define PRESETWIDGETCONTAINER_H

#include <QWidget>

namespace Ui {
    class PresetWidgetContainer;
}

class PresetWidgetContainer : public QWidget
{
    Q_OBJECT

public:
    explicit PresetWidgetContainer(const QMetaObject& optionMetaObj, QWidget *parent = nullptr);
    ~PresetWidgetContainer();

private:
    Ui::PresetWidgetContainer *ui;
    const QMetaObject& optionMetaObj;
};

#endif // PRESETWIDGETCONTAINER_H

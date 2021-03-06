#ifndef OTOFILEMULTIPLESAVEWIDGET_H
#define OTOFILEMULTIPLESAVEWIDGET_H

#include <QWidget>
#include "otofilesavewidgetabstract.h"


namespace Ui {
    class OtoFileMultipleSaveWidget;
}

class OtoFileMultipleSaveWidget : public OtoFileSaveWidgetAbstract
{
    Q_OBJECT

public:
    explicit OtoFileMultipleSaveWidget(QWidget *parent = nullptr);
    ~OtoFileMultipleSaveWidget();

private:
    Ui::OtoFileMultipleSaveWidget *ui;

    // OtoFileSaveWidgetAbstract interface
public:
    bool isSecondFileNameAvailable() const;
    void setSecondFileNameAvailable(bool value);
    void setSecondFileNameCheckBoxText(const QString& text);
    QString secondFileNameUsage() const;
    void setSecondFileNameUsage(const QString& value);

    // OtoFileSaveWidgetAbstract interface
public:
    OptionContainer getOptions() const;
    void setOptions(const OptionContainer& options);
};

#endif // OTOFILEMULTIPLESAVEWIDGET_H

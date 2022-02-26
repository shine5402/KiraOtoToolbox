#ifndef OTOFILEDIRECTSAVEWIDGET_H
#define OTOFILEDIRECTSAVEWIDGET_H

#include <QWidget>
#include "otofilesavewidgetabstract.h"


namespace Ui {
    class OtoFileDirectSaveWidget;
}

class OtoFileDirectSaveWidget : public OtoFileSaveWidgetAbstract
{
    Q_OBJECT

public:
    explicit OtoFileDirectSaveWidget(QWidget *parent = nullptr);
    ~OtoFileDirectSaveWidget();

    void setInfoText(QString text);

private:
    Ui::OtoFileDirectSaveWidget *ui;

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

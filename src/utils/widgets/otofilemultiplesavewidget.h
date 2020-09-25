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
    bool isSaveToSrc() const;
    bool isSaveToCustom() const;
    QString fileName() const;
    bool isSecondFileNameUsed() const;
    QString secondFileName() const;
    void setSaveToSrc();
    void setSaveToCustom();
    void setFileName(const QString& value);
    void setSecondFileNameUsed(bool value);
    void setSecondFileName(const QString& value);
    bool isSecondFileNameAvailable() const;
    void setSecondFileNameAvailable(bool value);
    void setSecondFileNameCheckBoxText(const QString& text);
    QString secondFileNameUsage() const;
    void setSecondFileNameUsage(const QString& value);
};

#endif // OTOFILEMULTIPLESAVEWIDGET_H

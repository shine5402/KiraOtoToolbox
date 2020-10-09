#ifndef OTOFILESAVEWIDGETABSTRACT_H
#define OTOFILESAVEWIDGETABSTRACT_H

#include <QWidget>

class OtoFileSaveWidgetAbstract : public QWidget
{
    Q_OBJECT
public:
    explicit OtoFileSaveWidgetAbstract(QWidget *parent = nullptr);

    virtual bool isSaveToSrc() const = 0;
    virtual bool isSaveToCustom() const = 0;
    virtual QString fileName() const = 0;
    virtual bool isSecondFileNameUsed() const = 0;
    virtual QString secondFileName() const = 0;

    virtual void setSaveToSrc() = 0;
    virtual void setSaveToCustom() = 0;
    virtual void setFileName(const QString& value) = 0;
    virtual void setSecondFileNameUsed(bool value) = 0;
    virtual void setSecondFileName(const QString& value) = 0;

    virtual bool isSecondFileNameAvailable() const = 0;
    virtual void setSecondFileNameAvailable(bool value) = 0;
    virtual void setSecondFileNameCheckBoxText(const QString& text) = 0;

    virtual QString secondFileNameUsage() const = 0;
    virtual void setSecondFileNameUsage(const QString& value) = 0;

signals:

};

#endif // OTOFILESAVEWIDGETABSTRACT_H

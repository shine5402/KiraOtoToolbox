#ifndef OTOFILESAVEWIDGETABSTRACT_H
#define OTOFILESAVEWIDGETABSTRACT_H

#include <QWidget>
#include "toolBase/optioncontainer.h"

class OtoFileSaveWidgetAbstract : public QWidget
{
    Q_OBJECT
public:
    explicit OtoFileSaveWidgetAbstract(QWidget *parent = nullptr);

    virtual OptionContainer getOptions() const = 0;
    virtual void setOptions(const OptionContainer &options) = 0;

    virtual bool isSecondFileNameAvailable() const = 0;
    virtual void setSecondFileNameAvailable(bool value) = 0;
    virtual void setSecondFileNameCheckBoxText(const QString& text) = 0;

    virtual QString secondFileNameUsage() const = 0;
    virtual void setSecondFileNameUsage(const QString& value) = 0;
};

#endif // OTOFILESAVEWIDGETABSTRACT_H

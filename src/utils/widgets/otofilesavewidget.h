#ifndef OTOFILESAVEWIDGET_H
#define OTOFILESAVEWIDGET_H

#include <QWidget>
#include "otofilesavewidgetabstract.h"

namespace Ui {
    class OtoFileSaveWidget;
}

class OtoFileSaveWidget : public OtoFileSaveWidgetAbstract
{
    Q_OBJECT

public:
    explicit OtoFileSaveWidget(QWidget *parent = nullptr);
    ~OtoFileSaveWidget();

    bool isSecondFileNameAvailable() const;
    void setSecondFileNameAvailable(bool value);
    void setSecondFileNameCheckBoxText(const QString& text);

    QString secondFileNameUsage() const;
    void setSecondFileNameUsage(const QString& value);

private:
    Ui::OtoFileSaveWidget *ui;
    bool m_secondFileNameAvailable = false;
    void refreshSecondFileNameWidgetVisible();
    QString m_secondFileNameUsage{};

    // OtoFileSaveWidgetAbstract interface
public:
    OptionContainer getOptions() const;
    void setOptions(const OptionContainer& options);
};

class OtoFileSaveWidgetWithSecondFileName : public OtoFileSaveWidget {
    Q_OBJECT

public:
    explicit OtoFileSaveWidgetWithSecondFileName(QWidget *parent = nullptr);
};

class OtoFileSaveWidgetWithSecondFileNameAsDeleted : public OtoFileSaveWidgetWithSecondFileName {
    Q_OBJECT

public:
    explicit OtoFileSaveWidgetWithSecondFileNameAsDeleted(QWidget *parent = nullptr);
};
#endif // OTOFILESAVEWIDGET_H


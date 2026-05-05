#ifndef JAVASCRIPTTOOLOPTIONWIDGET_H
#define JAVASCRIPTTOOLOPTIONWIDGET_H

#include <QWidget>

#include "toolBase/ToolOptionWidget.h"

namespace QSourceHighlite {
class QSourceHighliter;
}

namespace Ui {
class JavaScriptToolOptionWidget;
}

class JavaScriptToolOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit JavaScriptToolOptionWidget(QWidget *parent = nullptr);
    ~JavaScriptToolOptionWidget();

protected:
    void changeEvent(QEvent *event) override;

private slots:
    void refillLineNumbers();
    void syncCursors();

private:
    void applyTheme();

    Ui::JavaScriptToolOptionWidget *ui;
    QSourceHighlite::QSourceHighliter *highlighter;

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer &options) override;
    QJsonObject optionsToJson(const OptionContainer &options) const override;
    OptionContainer jsonToOptions(const QJsonObject &json) const override;
    int optionJsonVersion() const override;
};

#endif // JAVASCRIPTTOOLOPTIONWIDGET_H

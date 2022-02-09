#ifndef COPYORREPLACEBYALIASOPTIONWIDGET_H
#define COPYORREPLACEBYALIASOPTIONWIDGET_H

#include <QWidget>
#include <toolBase/tooloptionwidget.h>

namespace Ui {
    class CopyOrReplaceByAliasOptionWidget;
}

class CopyOrReplaceByAliasOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit CopyOrReplaceByAliasOptionWidget(QWidget *parent = nullptr);
    ~CopyOrReplaceByAliasOptionWidget();

private:
    Ui::CopyOrReplaceByAliasOptionWidget *ui;

public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
    QJsonObject optionsToJson(const OptionContainer& options) const override;
    OptionContainer jsonToOptions(const QJsonObject& json) const override;
    int optionJsonVersion() const override;
};

#endif // COPYORREPLACEBYALIASOPTIONWIDGET_H

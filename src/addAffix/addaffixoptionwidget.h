#ifndef ADDAFFIXOPTIONWIDGET_H
#define ADDAFFIXOPTIONWIDGET_H

#include <QWidget>
#include <toolBase/tooloptionwidget.h>
#include <QLineEdit>

class AddAffixOptionWidget : public ToolOptionWidget
{
    Q_OBJECT
public:
    explicit AddAffixOptionWidget(QWidget *parent = nullptr);
    ToolOptions * getOptions(QObject *parent = nullptr) const override;
    void setOptions(const ToolOptions *options) override;
private:
    QLineEdit* prefixEdit;
    QLineEdit* suffixEdit;
};

#endif // ADDAFFIXOPTIONWIDGET_H

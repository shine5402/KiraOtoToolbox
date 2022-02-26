#ifndef REPLACERULESWIDGET_H
#define REPLACERULESWIDGET_H

#include "replacerulesmodel.h"
#include <QWidget>

namespace Ui {
    class ReplaceRulesWidget;
}

class ReplaceRulesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReplaceRulesWidget(QWidget *parent = nullptr);
    ~ReplaceRulesWidget();

    QVector<ReplaceRule> getRules() const;
    void setRules(const QVector<ReplaceRule>& value);

private slots:
    void addRule();
    void removeRule();
    void multiLineEdit();
    void moveUpRule();
    void moveDownRule();
    void sortRuleByMatchPatternLength();

private:
    Ui::ReplaceRulesWidget *ui;
    ReplaceRulesModel* model;

signals:
    void rulesChanged();
};

#endif // REPLACERULESWIDGET_H

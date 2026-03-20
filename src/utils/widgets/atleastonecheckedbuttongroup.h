#ifndef ATLEASTONECHECKEDBUTTONGROUP_H
#define ATLEASTONECHECKEDBUTTONGROUP_H

#include <QObject>
#include <QAbstractButton>

class QButtonGroup;

class AtLeastOneCheckedButtonGroup : public QObject
{
    Q_OBJECT
public:
    explicit AtLeastOneCheckedButtonGroup(QObject *parent = nullptr);
    void addButton(QAbstractButton *button, int id = -1);
    QAbstractButton* button(int id) const;
    QList<QAbstractButton*> buttons() const;
    QList<QAbstractButton*> checkedButtons() const;
    QList<int> checkedIds() const;
    int id(QAbstractButton* button) const;
    void removeButton(QAbstractButton* button);
    void setId(QAbstractButton *button, int id);

private:
    QButtonGroup* groupInside;
private slots:
    void checkCheckedState(QAbstractButton *button);
signals:
    void buttonClicked(int id);
    void buttonClicked(QAbstractButton *button);
    void buttonPressed(int id);
    void buttonPressed(QAbstractButton *button);
    void buttonReleased(int id);
    void buttonReleased(QAbstractButton *button);
    void buttonToggled(int id, bool checked);
    void buttonToggled(QAbstractButton *button, bool checked);

};

#endif // ATLEASTONECHECKEDBUTTONGROUP_H

#include "atleastonecheckedbuttongroup.h"
#include <QButtonGroup>

//FIXME: not use enabled

AtLeastOneCheckedButtonGroup::AtLeastOneCheckedButtonGroup(QObject *parent) : QObject(parent)
{
    groupInside = new QButtonGroup(this);
    groupInside->setExclusive(false);
    connect(groupInside, &QButtonGroup::idClicked, this, qOverload<int>(&AtLeastOneCheckedButtonGroup::buttonClicked));
    connect(groupInside, qOverload<QAbstractButton *>(&QButtonGroup::buttonClicked), this, qOverload<QAbstractButton *>(&AtLeastOneCheckedButtonGroup::buttonClicked));
    connect(groupInside, &QButtonGroup::idClicked, this, qOverload<int>(&AtLeastOneCheckedButtonGroup::buttonPressed));
    connect(groupInside, qOverload<QAbstractButton *>(&QButtonGroup::buttonPressed), this, qOverload<QAbstractButton *>(&AtLeastOneCheckedButtonGroup::buttonPressed));
    connect(groupInside, &QButtonGroup::idClicked, this, qOverload<int>(&AtLeastOneCheckedButtonGroup::buttonReleased));
    connect(groupInside, qOverload<QAbstractButton *>(&QButtonGroup::buttonReleased), this, qOverload<QAbstractButton *>(&AtLeastOneCheckedButtonGroup::buttonReleased));
    connect(groupInside, &QButtonGroup::idToggled, this, qOverload<int, bool>(&AtLeastOneCheckedButtonGroup::buttonToggled));
    connect(groupInside, qOverload<QAbstractButton *, bool>(&QButtonGroup::buttonToggled), this, qOverload<QAbstractButton *, bool>(&AtLeastOneCheckedButtonGroup::buttonToggled));
    connect(this, qOverload<int, bool>(&AtLeastOneCheckedButtonGroup::buttonToggled), this, &AtLeastOneCheckedButtonGroup::updateEnableState);
}

void AtLeastOneCheckedButtonGroup::addButton(QAbstractButton* button, int id)
{
    groupInside->addButton(button, id);
}

QAbstractButton* AtLeastOneCheckedButtonGroup::button(int id) const
{
    return groupInside->button(id);
}

QList<QAbstractButton*> AtLeastOneCheckedButtonGroup::buttons() const
{
    return groupInside->buttons();
}

QList<QAbstractButton*> AtLeastOneCheckedButtonGroup::checkedButtons() const
{
    QList<QAbstractButton*> result;
    for (auto b : buttons()){
        if (b->isChecked())
            result.append(b);
    }
    return result;
}

QList<int> AtLeastOneCheckedButtonGroup::checkedIds() const
{
    auto buttons = checkedButtons();
    QList<int> result;
    for (auto b : buttons){
        result.append(id(b));
    }
    return result;
}

int AtLeastOneCheckedButtonGroup::id(QAbstractButton* button) const
{
    return groupInside->id(button);
}

void AtLeastOneCheckedButtonGroup::updateEnableState()
{
    if (checkedButtons().count() == 1){
        for (auto b : buttons()){
            b->setEnabled(!b->isChecked());
        }
    }
    else
    {
        for (auto b : buttons()){
            b->setEnabled(true);
        }
    }
}


#include "atleastonecheckedbuttongroup.h"
#include <QButtonGroup>
#include "../lib/misc/qballontip.h"
#include <QStyle>
#include <QApplication>

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
    connect(this, qOverload<QAbstractButton *>(&AtLeastOneCheckedButtonGroup::buttonClicked), this, &AtLeastOneCheckedButtonGroup::checkCheckedState);
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
    const auto buttons_ = buttons();
    for (auto b : buttons_){
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

void AtLeastOneCheckedButtonGroup::checkCheckedState(QAbstractButton* button)
{
    if (checkedButtons().count() < 1){
    QBalloonTip::showBalloon(qApp->style()->standardIcon(QStyle::SP_MessageBoxWarning),
    tr("必须至少选择一项"), tr("您应当至少选择一项作为输入。"), button, QCursor::pos(), 3000);
    button->toggle();
    }
}


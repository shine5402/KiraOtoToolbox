#include "chainstepsmodel.h"
#include "toolBase/tooldialogadapter.h"

ChainStepsModel::ChainStepsModel(const QVector<ChainElement>& steps, QObject *parent)
    : QAbstractListModel(parent), steps(steps)
{
}

int ChainStepsModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return steps.count();
}

QVariant ChainStepsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.row() < steps.count()){
            return steps.at(index.row()).toolName();
        }
    }
    return QVariant();
}

int ChainStepsModel::stepCount() const
{
    return steps.count();
}

void ChainStepsModel::addStep(const ChainElement& step)
{
    beginInsertRows(QModelIndex{}, steps.count(), steps.count());
    steps.append(step);
    endInsertRows();
}

void ChainStepsModel::removeStep(int index)
{
    beginRemoveRows(QModelIndex{}, index, index);
    steps.removeAt(index);
    endRemoveRows();
}

void ChainStepsModel::moveUpStep(int index)
{
    if (index > 0){
        beginMoveRows(QModelIndex{}, index, index, QModelIndex{}, index - 1);
        std::swap(steps[index], steps[index - 1]);
        endMoveRows();
    }
}

void ChainStepsModel::moveDownStep(int index)
{
    if (index < steps.count() - 1){
        beginMoveRows(QModelIndex{}, index, index, QModelIndex{}, index + 2);
        std::swap(steps[index], steps[index + 1]);
        endMoveRows();
    }
}

const ChainElement& ChainStepsModel::getStep(int index) const
{
    return steps.at(index);
}

void ChainStepsModel::setStep(int index, const ChainElement& value)
{
    steps[index] = value;
}

void ChainStepsModel::setStepOptions(int index, const OptionContainer& value)
{
    steps[index].options = value;
}

QVector<ChainElement> ChainStepsModel::getSteps() const
{
    return steps;
}

void ChainStepsModel::setSteps(const QVector<ChainElement>& value)
{
    beginResetModel();
    steps = value;
    endResetModel();
}

#include "chainstepsmodel.h"

ChainStepsModel::ChainStepsModel(const QVector<Tool>& steps, QObject *parent)
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
        if (index.row() < steps.count())
            return steps.at(index.row()).getName();
    }
    return QVariant();
}

int ChainStepsModel::stepCount() const
{
    return steps.count();
}

void ChainStepsModel::addStep(const Tool& step)
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

const Tool& ChainStepsModel::getStep(int index) const
{
    return steps.at(index);
}

QVector<Tool> ChainStepsModel::getSteps() const
{
    return steps;
}

void ChainStepsModel::setSteps(const QVector<Tool>& value)
{
    beginResetModel();
    steps = value;
    endResetModel();
}

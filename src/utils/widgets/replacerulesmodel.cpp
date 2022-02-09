#include "replacerulesmodel.h"

ReplaceRulesModel::ReplaceRulesModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant ReplaceRulesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        switch (section) {
            case 0:return tr("Matching pattern");
            case 1:return tr("Replacing target");
            case 2:return tr("Matching strategy");
        }
    }

    return {};
}

int ReplaceRulesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return rules.count();
}

int ReplaceRulesModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant ReplaceRulesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole){
        auto currentRule = rules.at(index.row());
        switch (index.column()){
            case 0:return currentRule.matchPattern();
            case 1:return currentRule.targetPattern();
            case 2:return ReplaceRule::getStrategyString(currentRule.strategy());
        }
    }

    if (role == Qt::EditRole){
        auto currentRule = rules.at(index.row());
        switch (index.column()){
            case 0:return currentRule.matchPattern();
            case 1:return currentRule.targetPattern();
            case 2:return currentRule.strategy();
        }
    }

    return QVariant();
}

bool ReplaceRulesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == Qt::EditRole){
            auto currentRule = rules.at(index.row());
            switch (index.column()) {
                case 0:currentRule.setMatchPattern(value.toString());break;
                case 1:currentRule.setTargetPattern(value.toString());break;
                case 2:currentRule.setStrategy((ReplaceRule::MatchStrategy) value.toInt());break;
                default:return false;
            }
            rules[index.row()] = currentRule;
            emit dataChanged(index, index);
        }
        return true;
    }
    return false;
}

Qt::ItemFlags ReplaceRulesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemNeverHasChildren |Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVector<ReplaceRule> ReplaceRulesModel::getRules() const
{
    return rules;
}

void ReplaceRulesModel::setRules(const QVector<ReplaceRule>& value)
{
    beginResetModel();
    rules = value;
    endResetModel();
}

void ReplaceRulesModel::appendRule(const ReplaceRule& rule)
{
    beginInsertRows({}, rules.count(), rules.count());

    rules.append(rule);

    endInsertRows();
}

bool ReplaceRulesModel::removeRule(int index)
{
    if (index >= rules.count())
        return false;
    beginRemoveRows({}, index, index);

    rules.remove(index);

    endRemoveRows();

    return true;
}

void ReplaceRulesModel::moveUpRule(int index)
{
    if (index > 0){
        beginMoveRows(QModelIndex{}, index, index, QModelIndex{}, index - 1);
        std::swap(rules[index], rules[index - 1]);
        endMoveRows();
    }
}

void ReplaceRulesModel::moveDownRule(int index)
{
    if (index < rules.count() - 1){
        beginMoveRows(QModelIndex{}, index, index, QModelIndex{}, index + 2);
        std::swap(rules[index], rules[index + 1]);
        endMoveRows();
    }
}

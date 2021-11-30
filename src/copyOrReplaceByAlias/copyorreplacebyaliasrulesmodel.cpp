#include "copyorreplacebyaliasrulesmodel.h"

CopyOrReplaceByAliasRulesModel::CopyOrReplaceByAliasRulesModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant CopyOrReplaceByAliasRulesModel::headerData(int section, Qt::Orientation orientation, int role) const
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

int CopyOrReplaceByAliasRulesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return rules.count();
}

int CopyOrReplaceByAliasRulesModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant CopyOrReplaceByAliasRulesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole){
        auto currentRule = rules.at(index.row());
        switch (index.column()){
            case 0:return currentRule.matchPattern();
            case 1:return currentRule.targetPattern();
            case 2:return CopyOrReplaceByAliasRule::getStrategyString(currentRule.strategy());
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

bool CopyOrReplaceByAliasRulesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == Qt::EditRole){
            auto currentRule = rules.at(index.row());
            switch (index.column()) {
                case 0:currentRule.setMatchPattern(value.toString());break;
                case 1:currentRule.setTargetPattern(value.toString());break;
                case 2:currentRule.setStrategy((CopyOrReplaceByAliasRule::MatchStrategy) value.toInt());break;
                default:return false;
            }
            rules[index.row()] = currentRule;
            emit dataChanged(index, index);
        }
        return true;
    }
    return false;
}

Qt::ItemFlags CopyOrReplaceByAliasRulesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemNeverHasChildren |Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVector<CopyOrReplaceByAliasRule> CopyOrReplaceByAliasRulesModel::getRules() const
{
    return rules;
}

void CopyOrReplaceByAliasRulesModel::setRules(const QVector<CopyOrReplaceByAliasRule>& value)
{
    beginResetModel();
    rules = value;
    endResetModel();
}

void CopyOrReplaceByAliasRulesModel::appendRule(const CopyOrReplaceByAliasRule& rule)
{
    beginInsertRows({}, rules.count(), rules.count());

    rules.append(rule);

    endInsertRows();
}

bool CopyOrReplaceByAliasRulesModel::removeRule(int index)
{
    if (index >= rules.count())
        return false;
    beginRemoveRows({}, index, index);

    rules.remove(index);

    endRemoveRows();

    return true;
}

#ifndef COPYORREPLACEBYALIASRULESMODEL_H
#define COPYORREPLACEBYALIASRULESMODEL_H

#include <QAbstractTableModel>
#include "copyorreplacebyaliasrule.h"

class CopyOrReplaceByAliasRulesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CopyOrReplaceByAliasRulesModel(QObject *parent = nullptr);

    QVector<CopyOrReplaceByAliasRule> getRules() const;
    void setRules(const QVector<CopyOrReplaceByAliasRule>& value);

    void appendRule(const CopyOrReplaceByAliasRule& rule);
    bool removeRule(int index);
    void moveUpRule(int index);
    void moveDownRule(int index);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    QVector<CopyOrReplaceByAliasRule> rules;
};

#endif // COPYORREPLACEBYALIASRULESMODEL_H

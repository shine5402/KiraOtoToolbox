#ifndef REPLACERULESMODEL_H
#define REPLACERULESMODEL_H

#include <QAbstractTableModel>
#include "replacerule.h"

class ReplaceRulesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ReplaceRulesModel(QObject *parent = nullptr);

    QVector<ReplaceRule> getRules() const;
    void setRules(const QVector<ReplaceRule>& value);

    void appendRule(const ReplaceRule& rule);
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
    QVector<ReplaceRule> rules;
};

#endif // REPLACERULESMODEL_H

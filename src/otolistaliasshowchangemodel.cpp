#include "otolistaliasshowchangemodel.h"
#include <QFont>

OtoListAliasShowChangeModel::OtoListAliasShowChangeModel(const OtoEntryList* const entryList, const QStringList* const newAliasList, QObject *parent)
    : QAbstractTableModel(parent), entryList(entryList), newAliasList(newAliasList)
{
}

QVariant OtoListAliasShowChangeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section) {
            case FILENAME: return tr("文件名");
            case ALIAS: return tr("别名");
            case NEWALIAS: return tr("新的别名");
            case LEFT: return tr("左");
            case CONSONANT: return tr("固定范围");
            case RIGHT: return tr("右");
            case PREUTTERANCE: return tr("先行发声");
            case OVERLAP: return ("重叠");
        }
    }
    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
    {
        return QString::number(section + 1);
    }
    return {};
}

int OtoListAliasShowChangeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (!entryList)
        return 0;

    return entryList->count();
}

int OtoListAliasShowChangeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    constexpr int parameterCount = 8;
    return parameterCount;
}

QVariant OtoListAliasShowChangeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (!entryList)
        return {};

    if (role == Qt::DisplayRole)
    {
        auto oto = entryList->at(index.row());
        switch (index.column())
        {
            case FILENAME: return oto.fileName();
            case ALIAS: return oto.alias();
            case NEWALIAS: return (!newAliasList->at(index.row()).isEmpty()) ? newAliasList->at(index.row()) : oto.alias();
            case LEFT: return oto.left();
            case CONSONANT: return oto.consonant();
            case RIGHT: return oto.right();
            case PREUTTERANCE: return oto.preUtterance();
            case OVERLAP: return oto.overlap();
        }
    }
    if (role == Qt::FontRole)
    {
        if ((!newAliasList->at(index.row()).isEmpty()) && (newAliasList->at(index.row()) != entryList->at(index.row()).alias())){
            if (index.column() == ALIAS)
            {
                QFont font{};
                font.setItalic(true);
                return font;
            }
            if (index.column() == NEWALIAS)
            {
                QFont font{};
                font.setBold(true);
                return font;
            }
        }
    }
    return QVariant();
}

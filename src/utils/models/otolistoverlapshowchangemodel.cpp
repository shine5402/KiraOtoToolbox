#include "otolistoverlapshowchangemodel.h"
#include <QFont>

OtoListOverlapShowChangeModel::OtoListOverlapShowChangeModel(OtoEntryList* const entryList, QVector<double>* const newOverlapList, QObject *parent)
    : QAbstractTableModel(parent), entryList(entryList), newOverlapList(newOverlapList)
{
}

QVariant OtoListOverlapShowChangeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section) {
            case FILENAME: return tr("文件名");
            case ALIAS: return tr("别名");
            case LEFT: return tr("左");
            case CONSONANT: return tr("固定范围");
            case RIGHT: return tr("右");
            case PREUTTERANCE: return tr("先行发声");
            case OVERLAP: return ("重叠");
            case NEWOVERLAP: return tr("新的重叠");
        }
    }
    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
    {
        return QString::number(section + 1);
    }
    return {};
}

int OtoListOverlapShowChangeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (!entryList)
        return 0;

    return entryList->count();
}

int OtoListOverlapShowChangeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    constexpr int parameterCount = 8;
    return parameterCount;
}

QVariant OtoListOverlapShowChangeModel::data(const QModelIndex &index, int role) const
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
            case LEFT: return oto.left();
            case CONSONANT: return oto.consonant();
            case RIGHT: return oto.right();
            case PREUTTERANCE: return oto.preUtterance();
            case OVERLAP: return oto.overlap();
            case NEWOVERLAP: return QString::number(newOverlapList->at(index.row()),'f',3);
        }
    }
    if (role == Qt::FontRole)
    {
        auto doubleEqual = [] (double lhs, double rhs) -> bool
            {
                return std::abs(lhs - rhs) < 1e-3;
            };
        if (!doubleEqual(newOverlapList->at(index.row()) + 1, entryList->at(index.row()).overlap() + 1)){
            if (index.column() == OVERLAP)
            {
                QFont font{};
                font.setItalic(true);
                return font;
            }
            if (index.column() == NEWOVERLAP)
            {
                QFont font{};
                font.setBold(true);
                return font;
            }
        }
    }
    return QVariant();
}

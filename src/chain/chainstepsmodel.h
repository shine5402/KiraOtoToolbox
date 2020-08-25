#ifndef CHAINSTEPSMODEL_H
#define CHAINSTEPSMODEL_H

#include <QAbstractListModel>
#include "toolBase/toolmanager.h"

class ChainStepsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ChainStepsModel(const QVector<Tool>& steps = {}, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int stepCount() const;
    void addStep(const Tool& step);
    void removeStep(int index);
    void moveUpStep(int index);
    void moveDownStep(int index);
    const Tool& getStep(int index) const;

    QVector<Tool> getSteps() const;

    void setSteps(const QVector<Tool>& value);

public slots:

private:
    QVector<Tool> steps;
};

#endif // CHAINSTEPSMODEL_H

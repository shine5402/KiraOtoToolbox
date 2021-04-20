#ifndef CHAINSTEPSMODEL_H
#define CHAINSTEPSMODEL_H

#include <QAbstractListModel>
#include "chainelement.h"

class ChainStepsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ChainStepsModel(const QVector<ChainElement>& steps = {}, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int stepCount() const;
    void addStep(const ChainElement& step);
    void removeStep(int index);
    void moveUpStep(int index);
    void moveDownStep(int index);
    const ChainElement& getStep(int index) const;
    void setStep(int index, const ChainElement& value);
    void setStepOptions(int index, const OptionContainer& value);

    QVector<ChainElement> getSteps() const;

    void setSteps(const QVector<ChainElement>& value);

public slots:

private:
    QVector<ChainElement> steps;
};

#endif // CHAINSTEPSMODEL_H

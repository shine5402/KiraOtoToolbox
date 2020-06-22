#ifndef REMOVESUFFIXOTOLISTTASK_H
#define REMOVESUFFIXOTOLISTTASK_H

#include <QObject>
#include "../toolBase/otolisttask.h"

class RemoveSuffixOtoListTask : public OtoListTask
{
    Q_OBJECT
public:
    explicit RemoveSuffixOtoListTask(QObject* parent = nullptr);
    bool doTask(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* options) override;
};

#endif // REMOVESUFFIXOTOLISTTASK_H

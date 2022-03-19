#ifndef VOWELCROSSFADINGOTOLISTMODIFYWORKER_H
#define VOWELCROSSFADINGOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>

class VowelCrossfadingOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VowelCrossfadingOtoListModifyWorker(QObject* parent = nullptr);

    void doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;
};

#endif // VOWELCROSSFADINGOTOLISTMODIFYWORKER_H

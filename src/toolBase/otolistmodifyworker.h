#ifndef OTOPROCESSOR_H
#define OTOPROCESSOR_H

#include <QObject>
#include <otoentry.h>
#include "tooloptions.h"

class OtoListModifyWorker : public QObject
{
    Q_OBJECT
public:
    explicit OtoListModifyWorker(QObject *parent = nullptr);
    virtual bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList,
                               const ToolOptions& options) = 0;
};

#endif // OTOPROCESSOR_H

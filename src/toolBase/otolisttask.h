#ifndef OTOPROCESSOR_H
#define OTOPROCESSOR_H

#include <QObject>
#include <otoentry.h>
#include "tooloptions.h"

class OtoListTask : public QObject
{
    Q_OBJECT
public:
    explicit OtoListTask(QObject *parent = nullptr);
    virtual bool doTask(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList,
                               const ToolOptions* options) = 0;
};

#endif // OTOPROCESSOR_H

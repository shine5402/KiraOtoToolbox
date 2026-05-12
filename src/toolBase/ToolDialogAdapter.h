#ifndef TOOLDIALOGADAPTER_H
#define TOOLDIALOGADAPTER_H

#include <QLayout>
#include <QObject>
#include <QPointer>

#include "ToolException.h"
#include "toolBase/OtoListModifyWorker.h"
#include "toolBase/ToolOptionWidget.h"
#include "utils/widgets/OtoFileLoadWidget.h"
#include "utils/widgets/OtoFileSaveWidget.h"

enum class ToolCategory {
    EntryOperations,
    ValueOperations,
    AliasOperations,
    FilenameActions,
    MetaActions
};

class ToolDialogAdapter : public QObject
{
    Q_OBJECT
public:
    explicit ToolDialogAdapter(QObject *parent = nullptr);
    virtual void replaceUIWidgets(QLayout *rootLayout);
    virtual bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList,
                        const OptionContainer &options, QWidget *dialogParent);
    virtual QString getToolName() const = 0;
    virtual ToolCategory getToolCategory() const = 0;

    static QString categoryDisplayName(ToolCategory category);

    QMetaObject getOptionWidgetMetaObj() const;
    QMetaObject getWorkerMetaObj() const;
    std::unique_ptr<OtoListModifyWorker> getWorkerInstance() const;

protected:
    static void replaceSaveWidget(QLayout *rootLayout, OtoFileSaveWidget *newSaveWidget);
    void setOptionWidgetMetaObj(const QMetaObject &value);
    void setWorkerMetaObj(const QMetaObject &value);

private:
    QMetaObject optionWidgetMetaObj;
    QMetaObject workerMetaObj;
signals:
};

#endif // TOOLDIALOGADAPTER_H

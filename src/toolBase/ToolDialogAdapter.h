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

class ToolDialogAdapter : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ToolDialogAdapter(QObject *parent = nullptr);
    virtual void replaceUIWidgets(QLayout *rootLayout);
    virtual bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList,
                        const OptionContainer &options, QWidget *dialogParent);
    virtual QString getToolName() const;

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

#include <QCoreApplication>
#define DEFINE_TOOL_NAME(name)                                                                                         \
    static constexpr auto TOOL_NAME = name;                                                                            \
    QString getToolName() const override                                                                               \
    {                                                                                                                  \
        return QCoreApplication::translate("TOOL_NAME", name);                                                         \
    }

#endif // TOOLDIALOGADAPTER_H

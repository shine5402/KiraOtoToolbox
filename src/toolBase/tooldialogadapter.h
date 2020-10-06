#ifndef TOOLDIALOGADAPTER_H
#define TOOLDIALOGADAPTER_H

#include <QObject>
#include <QLayout>
#include "utils/widgets/otofileloadwidget.h"
#include "utils/widgets/otofilesavewidget.h"
#include "toolBase/tooloptionwidget.h"
#include "toolBase/otolistmodifyworker.h"
#include <QPointer>

//TODO:Test

namespace ToolDialogAdapterHelperFunc {
    void replaceWidget(QLayout* parentLayout, const QString& widgetName, QWidget* newWidget, QWidget* newParent = nullptr);
}

class ToolDialogAdapter : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ToolDialogAdapter(QObject *parent = nullptr);
    virtual void replaceUIWidgets(QLayout* rootLayout);
    virtual bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList,
                               const ToolOptions& options, QWidget* dialogParent);
    virtual bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList,
                        const ToolOptions& options);
    virtual QString getToolName() const;

protected:
    void replaceOptionWidget(QLayout* rootLayout, ToolOptionWidget* newOptionWidget);
    void replaceSaveWidget(QLayout* rootLayout, OtoFileSaveWidget* newSaveWidget);
    OtoListModifyWorker* getWorker() const;
    void setWorker(OtoListModifyWorker* value);
    void setOptionWidget(ToolOptionWidget* value);

    enum ChangeAskDialogType{
        ValueChangeModel, Diff
    };

    static bool askUserForApplyChanges(const OtoEntryList& srcOtoList, const OtoEntryList& resultOtoList, ChangeAskDialogType changeType,
                                       const QString& title, const QString& label, QWidget* dialogParent);
    static bool askUserForSecondSave(const OtoEntryList& secondSaveData, const QString& title, const QString& label, QWidget* dialogParent);
private:
        QPointer<OtoListModifyWorker> worker = nullptr;
    QPointer<ToolOptionWidget> optionWidget = nullptr;
signals:

    friend class Tool;
};

#endif // TOOLDIALOGADAPTER_H

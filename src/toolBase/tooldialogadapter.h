#ifndef TOOLDIALOGADAPTER_H
#define TOOLDIALOGADAPTER_H

#include <QObject>
#include <QLayout>
#include "utils/widgets/otofileloadwidget.h"
#include "utils/widgets/otofilesavewidget.h"
#include "toolBase/tooloptionwidget.h"
#include "toolBase/otolistmodifyworker.h"

//TODO:Test

class ToolDialogAdapter : public QObject
{
    Q_OBJECT
public:
    explicit ToolDialogAdapter(QObject *parent = nullptr);
    virtual void setupSpecificUIWidgets(QLayout* rootLayout);
    bool doWork(const OtoFileLoadWidget* loadWidget, const OtoFileSaveWidget* saveWidget,
                const ToolOptionWidget* optionWidget, QWidget* dialogParent);
    virtual bool doWorkAdapter(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList,
                               const ToolOptions& options, QWidget* dialogParent);
    virtual QString getWindowTitle() const = 0;

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
    void replaceWidget(QLayout* parentLayout, const QString& widgetName, QWidget* newWidget, QWidget* newParent = nullptr);
    OtoListModifyWorker* worker = nullptr;
    //TODO: 存储optionWidget
    ToolOptionWidget* optionWidget = nullptr;
signals:

    friend class Tool;
};

#endif // TOOLDIALOGADAPTER_H

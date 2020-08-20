#ifndef TOOLDIALOGADAPTER_H
#define TOOLDIALOGADAPTER_H

#include <QObject>
#include <QLayout>
#include "utils/widgets/otofileloadwidget.h"
#include "utils/widgets/otofilesavewidget.h"
#include "toolBase/tooloptionwidget.h"

//TODO:Test

class ToolDialogAdapter : public QObject
{
    Q_OBJECT
public:
    explicit ToolDialogAdapter(QObject *parent = nullptr);
    virtual void setupSpecificUIWidgets(QLayout* rootLayout) = 0;
    bool doWork(const OtoFileLoadWidget* loadWidget, const OtoFileSaveWidget* saveWidget,
                        const ToolOptionWidget* optionWidget, QWidget* dialogParent);
    virtual bool doWorkAdapter(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList,
                               const ToolOptions* abstractOptions, QWidget* dialogParent) = 0;
    virtual QString getWindowTitle() const = 0;
protected:
    void replaceOptionWidget(QLayout* rootLayout, ToolOptionWidget* newOptionWidget);
    void replaceSaveWidget(QLayout* rootLayout, OtoFileSaveWidget* newSaveWidget);

    enum ChangeType{
        Value, Line
    };

    static bool askUserForApplyChanges(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, ChangeType changeType, OtoEntryList& secondSaveOtoList,
                                        const QString& title, const QString& label, QWidget* dialogParent);
private:
    void replaceWidget(QLayout* parentLayout, const QString& widgetName, QWidget* newWidget, QWidget* newParent = nullptr);
signals:

};

#endif // TOOLDIALOGADAPTER_H

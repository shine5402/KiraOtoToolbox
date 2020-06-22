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
    virtual bool processOtoList(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList,
                               const ToolOptions* abstractOptions, QWidget* dialogParent) = 0;
    bool askUserForApplyChanges(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList,
                                        const QString& title, const QString& label, QWidget* dialogParent){};//FIXME: 之后转为抽象函数
protected:
    void replaceOptionWidget(QLayout* rootLayout, ToolOptionWidget* newOptionWidget);
    void replaceSaveWidget(QLayout* rootLayout, OtoFileSaveWidget* newSaveWidget);

private:
    void replaceWidget(QLayout* parentLayout, const QString& widgetName, QWidget* newWidget, QWidget* newParent = nullptr);
signals:

};

#endif // TOOLDIALOGADAPTER_H

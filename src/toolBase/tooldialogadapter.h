#ifndef TOOLDIALOGADAPTER_H
#define TOOLDIALOGADAPTER_H

#include <QObject>
#include <QLayout>
#include "utils/widgets/otofileloadwidget.h"
#include "utils/widgets/otofilesavewidget.h"
#include "toolBase/tooloptionwidget.h"

class ToolDialogAdapter : public QObject
{
    Q_OBJECT
public:
    explicit ToolDialogAdapter(QObject *parent = nullptr);
    virtual void setupSpecificUIWidgets(QLayout* rootLayout) = 0;
    virtual bool doWork(const OtoFileLoadWidget* loadWidget, const OtoFileSaveWidget* saveWidget,
                        const ToolOptionWidget* optionWidget, QWidget* dialogParent) = 0;
signals:

};

#endif // TOOLDIALOGADAPTER_H

#ifndef CV_VCPARTDETACHTOOLDIALOGADAPTER_H
#define CV_VCPARTDETACHTOOLDIALOGADAPTER_H

#include "../toolBase/tooldialogadapter.h"

class CV_VCPartDetachToolDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    explicit CV_VCPartDetachToolDialogAdapter(QObject *parent = nullptr);

    // ToolDialogAdapter interface
public:
    void replaceUIWidgets(QLayout* rootLayout) override;
    QString getToolName() const override;
};

#endif // CV_VCPARTDETACHTOOLDIALOGADAPTER_H

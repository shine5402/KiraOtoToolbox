#ifndef CV_VCPARTSPLITTOOLDIALOGADAPTER_H
#define CV_VCPARTSPLITTOOLDIALOGADAPTER_H

#include "../toolBase/tooldialogadapter.h"

class CV_VCPartSplitToolDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit CV_VCPartSplitToolDialogAdapter(QObject *parent = nullptr);

    void replaceUIWidgets(QLayout* rootLayout) override;
    bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                OtoEntryList& secondSaveOtoList, const OptionContainer& options, QWidget* dialogParent) override;

    DEFINE_TOOL_NAME("Extract CV/VC part")
};

#endif // CV_VCPARTSPLITTOOLDIALOGADAPTER_H

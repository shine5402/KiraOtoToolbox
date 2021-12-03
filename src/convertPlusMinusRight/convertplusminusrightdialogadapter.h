#ifndef CONVERTPLUSMINUSRIGHTDIALOGADAPTER_H
#define CONVERTPLUSMINUSRIGHTDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class ConvertPlusMinusRightDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE ConvertPlusMinusRightDialogAdapter(QObject* parent = nullptr);
    DEFINE_TOOL_NAME("Convert ±right value")

    // ToolDialogAdapter interface
public:
    bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options, QWidget* dialogParent) override;
    bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;
};

#endif // CONVERTPLUSMINUSRIGHTDIALOGADAPTER_H

#ifndef CV_VCPARTSPLITTOOLDIALOGADAPTER_H
#define CV_VCPARTSPLITTOOLDIALOGADAPTER_H

#include "../toolBase/ToolDialogAdapter.h"

class CVVCPartSplitToolDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit CVVCPartSplitToolDialogAdapter(QObject *parent = nullptr);

    void replaceUIWidgets(QLayout *rootLayout) override;
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList,
                const OptionContainer &options, QWidget *dialogParent) override;

    Q_INVOKABLE static QString toolName() { return tr("Extract CV/VC part"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::EntryOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // CV_VCPARTSPLITTOOLDIALOGADAPTER_H

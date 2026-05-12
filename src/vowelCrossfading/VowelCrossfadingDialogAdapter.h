#ifndef VOWELCROSSFADINGDIALOGADAPTER_H
#define VOWELCROSSFADINGDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class VowelCrossfadingDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VowelCrossfadingDialogAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Vowel crossfading"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::ValueOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // VOWELCROSSFADINGDIALOGADAPTER_H

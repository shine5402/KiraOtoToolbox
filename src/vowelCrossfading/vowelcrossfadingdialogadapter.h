#ifndef VOWELCROSSFADINGDIALOGADAPTER_H
#define VOWELCROSSFADINGDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class VowelCrossfadingDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VowelCrossfadingDialogAdapter(QObject* parent = nullptr);
    DEFINE_TOOL_NAME("Vowel crossfading")
};

#endif // VOWELCROSSFADINGDIALOGADAPTER_H

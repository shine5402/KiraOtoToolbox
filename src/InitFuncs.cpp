#include "InitFuncs.h"
#include "removeDuplicate/RemoveDuplicateDialogAdapter.h"
#include "overlapBatchSet/OverlapBatchSetDialogAdapter.h"
#include "removeAffix/RemoveAffixDialogAdapter.h"
#include "addAffix/AddAffixDialogAdapter.h"
#include "addAffix/AddAffixOtoListModifyWorker.h"
#include "removeBlank/RemoveBlankDialogAdapter.h"
#include "removeBlank/RemoveBlankOtoListModifyWorker.h"
#include "chain/ChainDialogAdapter.h"
#include "notdoanything/NotDoAnythingDialogAdapter.h"
#include "cvvcPartSplit/CVVCPartSplitToolDialogAdapter.h"
#include "setAlias/SetAliasDialogAdapter.h"
#include "mergeOto/MergeOtoDialogAdapter.h"
#include <QCoreApplication>
#include "trimAroundSpecificValue/TrimAroundSpecificValueDialogAdapter.h"
#include "vowelCrossfading/VowelCrossfadingDialogAdapter.h"
#include "removeSpecificEntries/RemoveSpecificEntriesDialogAdapter.h"
#include "copyOrReplaceByAlias/CopyOrReplaceByAliasDialogAdapter.h"
#include "convertPlusMinusRight/ConvertPlusMinusRightDialogAdapter.h"
#include "preCenteredChangeValue/PreCenteredChangeValueAdapter.h"
#include "tempoTransform/TempoTransformDialogAdapter.h"
#include "replaceFileName/ReplaceFileNameAdapter.h"
#include "jsScript/JavaScriptToolDialogAdapter.h"

#define REGISTER_TOOL(type, adapter_class) \
    ToolManager::getManager()->registerTool(QCoreApplication::translate("TOOL_TYPE", type), adapter_class::staticMetaObject)

void registerTools()
{
    REGISTER_TOOL("Entry operations", RemoveDuplicateDialogAdapter);
    REGISTER_TOOL("Entry operations", RemoveBlankDialogAdapter);
    REGISTER_TOOL("Entry operations", MergeOtoDialogAdapter);
    REGISTER_TOOL("Entry operations", CVVCPartSplitToolDialogAdapter);
    REGISTER_TOOL("Entry operations", RemoveSpecificEntriesDialogAdapter);
    REGISTER_TOOL("Entry operations", CopyOrReplaceByAliasDialogAdapter);

    REGISTER_TOOL("Value operations", OverlapBatchSetDialogAdapter);
    REGISTER_TOOL("Value operations", VowelCrossfadingDialogAdapter);
    REGISTER_TOOL("Value operations", TrimAroundSpecificValueDialogAdapter);
    REGISTER_TOOL("Value operations", ConvertPlusMinusRightDialogAdapter);
    REGISTER_TOOL("Value operations", PreCenteredChangeValueAdapter);
    REGISTER_TOOL("Value operations", TempoTransformDialogAdapter);

    REGISTER_TOOL("Alias operations", RemoveAffixDialogAdapter);
    REGISTER_TOOL("Alias operations", AddAffixDialogAdapter);
    REGISTER_TOOL("Alias operations", SetAliasDialogAdapter);

    REGISTER_TOOL("Filename actions (maybe dangerous)", ReplaceFileNameAdapter);

    REGISTER_TOOL("Meta actions", JavaScriptToolDialogAdapter);
    REGISTER_TOOL("Meta actions", ChainDialogAdapter);
    REGISTER_TOOL("Meta actions", NotDoAnythingDialogAdapter);
}

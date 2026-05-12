#include "InitFuncs.h"

#include "addAffix/AddAffixDialogAdapter.h"
#include "chain/ChainDialogAdapter.h"
#include "convertPlusMinusRight/ConvertPlusMinusRightDialogAdapter.h"
#include "copyOrReplaceByAlias/CopyOrReplaceByAliasDialogAdapter.h"
#include "cvvcPartSplit/CVVCPartSplitToolDialogAdapter.h"
#include "jsScript/JavaScriptToolDialogAdapter.h"
#include "mergeOto/MergeOtoDialogAdapter.h"
#include "notDoAnything/NotDoAnythingDialogAdapter.h"
#include "overlapBatchSet/OverlapBatchSetDialogAdapter.h"
#include "preCenteredChangeValue/PreCenteredChangeValueAdapter.h"
#include "removeAffix/RemoveAffixDialogAdapter.h"
#include "removeBlank/RemoveBlankDialogAdapter.h"
#include "removeDuplicate/RemoveDuplicateDialogAdapter.h"
#include "removeSpecificEntries/RemoveSpecificEntriesDialogAdapter.h"
#include "replaceFileName/ReplaceFileNameAdapter.h"
#include "setAlias/SetAliasDialogAdapter.h"
#include "tempoTransform/TempoTransformDialogAdapter.h"
#include "trimAroundSpecificValue/TrimAroundSpecificValueDialogAdapter.h"
#include "vowelCrossfading/VowelCrossfadingDialogAdapter.h"

void registerTools()
{
    auto *mgr = ToolManager::getManager();

    mgr->registerTool<RemoveDuplicateDialogAdapter>();
    mgr->registerTool<RemoveBlankDialogAdapter>();
    mgr->registerTool<MergeOtoDialogAdapter>();
    mgr->registerTool<CVVCPartSplitToolDialogAdapter>();
    mgr->registerTool<RemoveSpecificEntriesDialogAdapter>();
    mgr->registerTool<CopyOrReplaceByAliasDialogAdapter>();

    mgr->registerTool<OverlapBatchSetDialogAdapter>();
    mgr->registerTool<VowelCrossfadingDialogAdapter>();
    mgr->registerTool<TrimAroundSpecificValueDialogAdapter>();
    mgr->registerTool<ConvertPlusMinusRightDialogAdapter>();
    mgr->registerTool<PreCenteredChangeValueAdapter>();
    mgr->registerTool<TempoTransformDialogAdapter>();

    mgr->registerTool<RemoveAffixDialogAdapter>();
    mgr->registerTool<AddAffixDialogAdapter>();
    mgr->registerTool<SetAliasDialogAdapter>();

    mgr->registerTool<ReplaceFileNameAdapter>();

    mgr->registerTool<JavaScriptToolDialogAdapter>();
    mgr->registerTool<ChainDialogAdapter>();
    mgr->registerTool<NotDoAnythingDialogAdapter>();
}

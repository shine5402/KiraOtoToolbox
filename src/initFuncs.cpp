#include "initFuncs.h"
#include "removeDuplicate/removeduplicatedialogadapter.h"
#include "overlapBatchSet/overlapbatchsetdialogadapter.h"
#include "removeAffix/removeaffixdialogadapter.h"
#include "addAffix/addaffixdialogadapter.h"
#include "addAffix/addaffixotolistmodifyworker.h"
#include "removeBlank/removeblankdialogadapter.h"
#include "removeBlank/removeblankotolistmodifyworker.h"
#include "chain/chaindialogadapter.h"
#include "notdoanything/notdoanythingdialogadapter.h"
#include "cv_vcPartSplit/cv_vcpartsplittooldialogadapter.h"
#include "setAlias/setaliasdialogadapter.h"
#include "mergeOto/mergeotodialogadapter.h"
#include <QCoreApplication>
#include "trimAroundSpecificValue/trimaroundspecificvaluedialogadapter.h"
#include "vowelCrossfading/vowelcrossfadingdialogadapter.h"
#include "removeSpecificEntries/removespecificentriesdialogadapter.h"
#include "copyOrReplaceByAlias/copyorreplacebyaliasdialogadapter.h"
#include "convertPlusMinusRight/convertplusminusrightdialogadapter.h"
#include "preCenteredChangeValue/precenteredchangevalueadapter.h"
#include "tempoTransform/tempotransfromdialogadapter.h"
#include "replaceFileName/replacefilenameadapter.h"

#define REGISTER_TOOL(type, adapter_class) \
    ToolManager::getManager()->registerTool(QCoreApplication::translate("TOOL_TYPE", type), adapter_class::staticMetaObject)

void registerTools()
{
    REGISTER_TOOL("Entry operations", RemoveDuplicateDialogAdapter);
    REGISTER_TOOL("Entry operations", RemoveBlankDialogAdapter);
    REGISTER_TOOL("Entry operations", MergeOtoDialogAdapter);
    REGISTER_TOOL("Entry operations", CV_VCPartSplitToolDialogAdapter);
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

    REGISTER_TOOL("Meta actions", ChainDialogAdapter);
    REGISTER_TOOL("Meta actions", NotDoAnythingDialogAdapter);
}

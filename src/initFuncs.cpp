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
#include <QCoreApplication>

#define REGISTER_TOOL(type, adapter_class) \
    ToolManager::getManager()->registerTool(QCoreApplication::translate("TOOL_TYPE", type), adapter_class::staticMetaObject)

void registerTools()
{
    REGISTER_TOOL("Remove unneeded entries", RemoveDuplicateDialogAdapter);
    REGISTER_TOOL("Remove unneeded entries", RemoveBlankDialogAdapter);
    REGISTER_TOOL("Set values in batch", OverlapBatchSetDialogAdapter);
    REGISTER_TOOL("Manipulate aliases", RemoveAffixDialogAdapter);
    REGISTER_TOOL("Manipulate aliases", AddAffixDialogAdapter);
    REGISTER_TOOL("Manipulate aliases", SetAliasDialogAdapter);
    REGISTER_TOOL("Filter what you need", CV_VCPartSplitToolDialogAdapter);
    REGISTER_TOOL("Meta actions", ChainDialogAdapter);
    REGISTER_TOOL("Meta actions", NotDoAnythingDialogAdapter);
}

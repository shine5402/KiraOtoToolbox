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
    REGISTER_TOOL("去除不需要的项", RemoveDuplicateDialogAdapter);
    REGISTER_TOOL("去除不需要的项", RemoveBlankDialogAdapter);
    REGISTER_TOOL("批量设置数值", OverlapBatchSetDialogAdapter);
    REGISTER_TOOL("对别名进行操作", RemoveAffixDialogAdapter);
    REGISTER_TOOL("对别名进行操作", AddAffixDialogAdapter);
    REGISTER_TOOL("对别名进行操作", SetAliasDialogAdapter);
    REGISTER_TOOL("筛选出需要的项", CV_VCPartSplitToolDialogAdapter);
    REGISTER_TOOL("元操作", ChainDialogAdapter);
    REGISTER_TOOL("元操作", NotDoAnythingDialogAdapter);
}

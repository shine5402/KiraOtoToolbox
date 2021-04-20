#include "registerTools.h"
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
#include <QCoreApplication>

//TODO:重构为临时建立新工具实例
void registerTools()
{
    auto manager = ToolManager::getManager();
    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "去除不需要的项"), new RemoveDuplicateDialogAdapter);
    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "去除不需要的项"), new RemoveBlankDialogAdapter);

    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "批量设置数值"), new OverlapBatchSetDialogAdapter);

    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "对别名进行操作"), new RemoveAffixDialogAdapter);
    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "对别名进行操作"), new AddAffixDialogAdapter);

    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "筛选出需要的项"), new CV_VCPartSplitToolDialogAdapter);

    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "元操作"), new ChainDialogAdapter);
    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "元操作"), new NotDoAnythingDialogAdapter);
}

//TODO:合并oto.ini文件
//TODO:别名替换/按规则复制

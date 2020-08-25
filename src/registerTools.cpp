#include "registerTools.h"
#include "removeDuplicate/removeduplicatedialogadapter.h"
#include "overlapBatchSet/overlapbatchsetdialogadapter.h"
#include "removeAffix/removeaffixdialogadapter.h"
#include "addAffix/addaffixdialogadapter.h"
#include "addAffix/addaffixotolistmodifyworker.h"
#include "removeBlank/removeblankdialogadapter.h"
#include "removeBlank/removeblankotolistmodifyworker.h"
#include "chain/chaindialogadapter.h"

void registerTools()
{
    auto manager = ToolManager::getManager();
    manager->registerTool(new RemoveDuplicateDialogAdapter);
    manager->registerTool(new OverlapBatchSetDialogAdapter);
    manager->registerTool(new RemoveAffixDialogAdapter);
    manager->registerTool(new AddAffixDialogAdapter);
    manager->registerTool(new RemoveBlankDialogAdapter);
    manager->registerTool(new ChainDialogAdapter);
}

//TODO:合并oto.ini文件
//TODO:别名替换/按规则复制

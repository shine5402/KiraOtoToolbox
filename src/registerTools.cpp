#include "registerTools.h"
#include "removeDuplicate/removeduplicatedialogadapter.h"
#include "overlapBatchSet/overlapbatchsetdialogadapter.h"
#include "removeAffix/removeaffixdialogadapter.h"
#include "addAffix/addaffixdialogadapter.h"
#include "addAffix/addaffixotolistmodifyworker.h"
#include "removeBlank/removeblankdialogadapter.h"
#include "removeBlank/removeblankotolistmodifyworker.h"
#include "chain/chaindialogadapter.h"
#include <QCoreApplication>

void registerTools()
{
    auto manager = ToolManager::getManager();
    manager->registerTool(QCoreApplication::translate("GLOBAL", "去除不需要的项"), new RemoveDuplicateDialogAdapter);
    manager->registerTool(QCoreApplication::translate("GLOBAL", "去除不需要的项"), new RemoveBlankDialogAdapter);

    manager->registerTool(QCoreApplication::translate("GLOBAL", "批量设置数值"), new OverlapBatchSetDialogAdapter);

    manager->registerTool(QCoreApplication::translate("GLOBAL", "对别名进行操作"), new RemoveAffixDialogAdapter);
    manager->registerTool(QCoreApplication::translate("GLOBAL", "对别名进行操作"), new AddAffixDialogAdapter);

    manager->registerTool(QCoreApplication::translate("GLOBAL", "元操作"), new ChainDialogAdapter);
}

//TODO:合并oto.ini文件
//TODO:别名替换/按规则复制

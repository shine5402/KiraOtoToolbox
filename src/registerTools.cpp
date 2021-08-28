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
#include "setAlias/setaliasdialogadapter.h"
#include <QCoreApplication>

void registerTools()
{
    auto manager = ToolManager::getManager();
    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "去除不需要的项"), RemoveDuplicateDialogAdapter::staticMetaObject);
    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "去除不需要的项"), RemoveBlankDialogAdapter::staticMetaObject);

    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "批量设置数值"), OverlapBatchSetDialogAdapter::staticMetaObject);

    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "对别名进行操作"), RemoveAffixDialogAdapter::staticMetaObject);
    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "对别名进行操作"), AddAffixDialogAdapter::staticMetaObject);
    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "对别名进行操作"), SetAliasDialogAdapter::staticMetaObject);

    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "筛选出需要的项"), CV_VCPartSplitToolDialogAdapter::staticMetaObject);

    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "元操作"), ChainDialogAdapter::staticMetaObject);
    manager->registerTool(QCoreApplication::translate("TOOL_TYPE", "元操作"), NotDoAnythingDialogAdapter::staticMetaObject);
}

//TODO:合并oto.ini文件
//TODO:别名替换/按规则复制

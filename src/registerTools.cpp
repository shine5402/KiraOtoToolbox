#include "registerTools.h"
#include "removeDuplicate/removeduplicatedialogadapter.h"
#include "removeDuplicate/removeduplicatemoduleotolistmodifyworker.h"
#include "overlapBatchSet/overlapbatchsetdialogadapter.h"
#include "overlapBatchSet/overlapbatchsetotolistmodifyworker.h"
#include "removeAffix/removeaffixdialogadapter.h"
#include "removeAffix/removeaffixotolistmodifyworker.h"
#include "addAffix/addaffixdialogadapter.h"
#include "addAffix/addaffixotolistmodifyworker.h"
#include "removeBlank/removeblankdialogadapter.h"
#include "removeBlank/removeblankotolistmodifyworker.h"

void registerTools()
{
    auto manager = ToolManager::getManager();
    manager->registerTool(new RemoveDuplicateDialogAdapter);
    manager->registerTool(new OverlapBatchSetDialogAdapter);
    manager->registerTool(new RemoveAffixDialogAdapter);
    manager->registerTool(new AddAffixDialogAdapter);
    manager->registerTool(new RemoveBlankDialogAdapter);
}

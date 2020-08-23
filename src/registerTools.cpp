#include "registerTools.h"
#include "removeDuplicate/removeduplicatedialogadapter.h"
#include "removeDuplicate/removeduplicatemoduleotolistmodifyworker.h"
#include "overlapBatchSet/overlapbatchsetdialogadapter.h"
#include "overlapBatchSet/overlapbatchsetotolistmodifyworker.h"
#include "removeAffix/removeaffixdialogadapter.h"
#include "removeAffix/removeaffixotolistmodifyworker.h"
#include "addAffix/addaffixdialogadapter.h"
#include "addAffix/addaffixotolistmodifyworker.h"

void registerTools()
{
    auto manager = ToolManager::getManager();
    manager->registerTool(new RemoveDuplicateModuleOtoListModifyWorker, new RemoveDuplicateDialogAdapter);
    manager->registerTool(new OverlapBatchSetOtoListModifyWorker, new OverlapBatchSetDialogAdapter);
    manager->registerTool(new RemoveAffixOtoListModifyWorker, new RemoveAffixDialogAdapter);
    manager->registerTool(new AddAffixOtoListModifyWorker, new AddAffixDialogAdapter);
}

#ifndef CHAINELEMENT_H
#define CHAINELEMENT_H

#include <QMetaObject>
#include <toolBase/optioncontainer.h>
#include <memory>
#include <toolBase/tooldialogadapter.h>

struct ChainElement
{
   QMetaObject toolAdapterMetaObj;
   QMetaObject toolModifyWorkerMetaObj;
   QMetaObject toolOptionWidgetMetaObj;
   OptionContainer options;

   QString toolName() const{
       if (auto toolAdapter = std::unique_ptr<ToolDialogAdapter>(
                   qobject_cast<ToolDialogAdapter *>(
                       toolAdapterMetaObj.newInstance()
                       ))){
           return toolAdapter->getToolName();
       }
       return {};
   }
};

Q_DECLARE_METATYPE(ChainElement)

#endif // CHAINELEMENT_H

#include "cv_vcpartdetachtooldialogadapter.h"
#include "cv_vcpartdetachoptionwidget.h"

CV_VCPartDetachToolDialogAdapter::CV_VCPartDetachToolDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{

}

void CV_VCPartDetachToolDialogAdapter::replaceUIWidgets(QLayout* rootLayout)
{
    auto saveWidget = new OtoFileSaveWidgetWithSecondFileName;
    saveWidget->setSecondFileNameCheckBoxText("分离VC部到新文件：");
    saveWidget->setSecondFileNameUsage("保存分离出来的VC部");
    replaceSaveWidget(rootLayout, saveWidget);
    replaceOptionWidget(rootLayout, new CV_VCPartDetachOptionWidget);
}

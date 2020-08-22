#include "otofilenameeditwithbrowse.h"

OtoFileNameEditWithBrowse::OtoFileNameEditWithBrowse(QWidget *parent) : FileNameEditWithBrowse(parent)
{

}

void OtoFileNameEditWithBrowse::setParametersByPurpose(const FileNameEditWithBrowse::Purpose& value)
{
    switch(value){
        case Open: setParameters(tr("选择一个原音设定文件"),{},tr("原音设定文件 (*.ini);;所有文件 (*.*)"));break;
        case Save: setParameters(tr("指定保存路径"), {}, tr("原音设定文件 (*.ini);;所有文件 (*.*)"));break;
    }
}

OtoFileNameEditWithOpenBrowse::OtoFileNameEditWithOpenBrowse(QWidget* parent) : OtoFileNameEditWithBrowse(parent)
{
    setParametersByPurpose(Open);
    setPurpose(Open);
}

OtoFileNameEditWithSaveBrowse::OtoFileNameEditWithSaveBrowse(QWidget* parent) : OtoFileNameEditWithBrowse(parent)
{
    setParametersByPurpose(Save);
    setPurpose(Save);
}

#include "otofilenameeditwithbrowse.h"

OtoFileNameEditWithBrowse::OtoFileNameEditWithBrowse(QWidget *parent) : FileNameEditWithBrowse(parent)
{

}

void OtoFileNameEditWithBrowse::setParametersByPurpose(const FileNameEditWithBrowse::Purpose& value)
{
    switch(value){
        case Open: setParameters(tr("Choose a oto file"),{},tr("Oto file (*.ini);;All files (*.*)"));break;
        case Save: setParameters(tr("Specify save path"), {}, tr("Oto file (*.ini);;:All files (*.*)"));break;
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

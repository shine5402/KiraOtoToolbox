#include "convertplusminusrightdialogadapter.h"
#include "convertplusminusrightoptionwidget.h"
#include "convertplusminusrightotolistmodifyworker.h"
#include <QMessageBox>

ConvertPlusMinusRightDialogAdapter::ConvertPlusMinusRightDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(ConvertPlusMinusRightOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(ConvertPlusMinusRightOptionWidget::staticMetaObject);
}


bool ConvertPlusMinusRightDialogAdapter::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options, QWidget* dialogParent)
{
    try {
        return ToolDialogAdapter::doWork(srcOtoList, resultOtoList, secondSaveOtoList, options, dialogParent);
    }
    catch(const ConvertPlusMinusRightOtoListModifyWorker::FileNotFoundException& e){
        QMessageBox::critical(dialogParent, {}, tr("The file \"%1\" don't exist. Please check and try again.").arg(e.fileName()));
    }
    catch(const ConvertPlusMinusRightOtoListModifyWorker::FileCannotReadException& e){
        QMessageBox::critical(dialogParent, {}, tr("Cannot open file \"%1\", or it contains invalid data. Please check and try again.").arg(e.fileName()));
    }
    catch(const ConvertPlusMinusRightOtoListModifyWorker::InvalidRightValue& e){
        QMessageBox::critical(dialogParent, {}, tr("Invalid right value\"%1\" has been calculated for oto \"%2\". Please check and try again.").arg(e.calculatedRight()).arg(e.entry().toString()));
    }
    return false;
}

bool ConvertPlusMinusRightDialogAdapter::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    try {
        return ToolDialogAdapter::doWork(srcOtoList, resultOtoList, secondSaveOtoList, options);
    }
    catch(const std::runtime_error&){
        return false;
    }
    return false;
}

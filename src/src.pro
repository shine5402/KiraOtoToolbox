QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = Shine5402OtoToolBox

VERSION = 0.4.0

RC_ICONS = resources/icon/appIcon.ico

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chain/chaindialogadapter.cpp \
    chain/chainotolistmodifyworker.cpp \
    chain/chainstepsmodel.cpp \
    chain/chaintooloptionwidget.cpp \
    cv_vcPartSplit/cv_vcpartsplitoptionwidget.cpp \
    cv_vcPartSplit/cv_vcpartsplitotolistmodifyworker.cpp \
    cv_vcPartSplit/cv_vcpartsplittooldialogadapter.cpp \
    i18n/translation.cpp \
    notdoanything/notdoanythingdialogadapter.cpp \
    notdoanything/notdoanythingoptionwidget.cpp \
    notdoanything/notdoanythingotolistmodifyworker.cpp \
    overlapBatchSet/overlapbatchsetotolistmodifyworker.cpp \
    registerTools.cpp \
    removeAffix/removeaffixdialogadapter.cpp \
    removeAffix/removeaffixoptionwidget.cpp \
    removeAffix/removeaffixotolistmodifyworker.cpp \
    removeAffix/removedstringinfo.cpp \
    removeAffix/removepitchaffixotolistmodifyworker.cpp \
    removeAffix/removespecificaffixotolistmodifyworker.cpp \
    addAffix/addaffixdialogadapter.cpp \
    addAffix/addaffixoptionwidget.cpp \
    addAffix/addaffixotolistmodifyworker.cpp \
    main.cpp \
    mainwindow.cpp \
    overlapBatchSet/overlapbatchsetdialogadapter.cpp \
    overlapBatchSet/overlapbatchsetdialogoptionwidget.cpp \
    removeBlank/removeblankdialogadapter.cpp \
    removeBlank/removeblankoptionwidget.cpp \
    removeBlank/removeblankotolistmodifyworker.cpp \
    removeDuplicate/orgnaizeduplicateotolistmodifyworker.cpp \
    removeDuplicate/removeduplicatedialogadapter.cpp \
    removeDuplicate/removeduplicatedialogoptionwidget.cpp \
    removeDuplicate/removeduplicatemoduleotolistmodifyworker.cpp \
    removeDuplicate/removeduplicateotolistmodifyworker.cpp \
    toolBase/optioncontainer.cpp \
    toolBase/otolistmodifyworker.cpp \
    toolBase/tooldialog.cpp \
    toolBase/tooldialogadapter.cpp \
    toolBase/toolmanager.cpp \
    toolBase/tooloptionwidget.cpp \
    utils/dialogs/listviewdialog.cpp \
    utils/dialogs/showdiffdialog.cpp \
    utils/dialogs/showotolistdialog.cpp \
    utils/dialogs/tableviewdialog.cpp \
    utils/misc/misc.cpp \
    utils/models/otofilelistwithpreviousmodel.cpp \
    utils/models/otolistmodel.cpp \
    utils/models/otolistshowvaluechangemodel.cpp \
    utils/widgets/atleastonecheckedbuttongroup.cpp \
    utils/widgets/filenameeditwithbrowse.cpp \
    utils/models/otofilelistmodel.cpp \
    utils/widgets/otofileloadwidget.cpp \
    utils/widgets/otofilemultipleloadwidget.cpp \
    utils/widgets/otofilemultiplesavewidget.cpp \
    utils/widgets/otofilenameeditwithbrowse.cpp \
    utils/widgets/otofilesavewidget.cpp \
    utils/widgets/otofilesavewidgetabstract.cpp \
    utils/widgets/stringlistmodifywidget.cpp

HEADERS += \
    chain/chaindialogadapter.h \
    chain/chainotolistmodifyworker.h \
    chain/chainstepsmodel.h \
    chain/chaintooloptionwidget.h \
    cv_vcPartSplit/cv_vcpartsplitoptionwidget.h \
    cv_vcPartSplit/cv_vcpartsplitotolistmodifyworker.h \
    cv_vcPartSplit/cv_vcpartsplittooldialogadapter.h \
    i18n/translation.h \
    notdoanything/notdoanythingdialogadapter.h \
    notdoanything/notdoanythingoptionwidget.h \
    notdoanything/notdoanythingotolistmodifyworker.h \
    overlapBatchSet/overlapbatchsetotolistmodifyworker.h \
    registerTools.h \
    removeAffix/removeaffixdialogadapter.h \
    removeAffix/removeaffixoptionwidget.h \
    removeAffix/removeaffixotolistmodifyworker.h \
    removeAffix/removedstringinfo.h \
    removeAffix/removepitchaffixotolistmodifyworker.h \
    removeAffix/removespecificaffixotolistmodifyworker.h \
    addAffix/addaffixdialogadapter.h \
    addAffix/addaffixoptionwidget.h \
    addAffix/addaffixotolistmodifyworker.h \
    mainwindow.h \
    overlapBatchSet/overlapbatchsetdialogadapter.h \
    overlapBatchSet/overlapbatchsetdialogoptionwidget.h \
    removeBlank/removeblankdialogadapter.h \
    removeBlank/removeblankoptionwidget.h \
    removeBlank/removeblankotolistmodifyworker.h \
    removeDuplicate/orgnaizeduplicateotolistmodifyworker.h \
    removeDuplicate/removeduplicatedialogadapter.h \
    removeDuplicate/removeduplicatedialogoptionwidget.h \
    removeDuplicate/removeduplicatemoduleotolistmodifyworker.h \
    removeDuplicate/removeduplicateotolistmodifyworker.h \
    toolBase/optioncontainer.h \
    toolBase/otolistmodifyworker.h \
    toolBase/tooldialog.h \
    toolBase/tooldialogadapter.h \
    toolBase/toolmanager.h \
    toolBase/tooloptionwidget.h \
    utils/dialogs/listviewdialog.h \
    utils/dialogs/showdiffdialog.h \
    utils/dialogs/showotolistdialog.h \
    utils/dialogs/tableviewdialog.h \
    utils/misc/fplusAdapter.h \
    utils/misc/misc.h \
    utils/models/otofilelistwithpreviousmodel.h \
    utils/models/otolistmodel.h \
    utils/models/otolistshowvaluechangemodel.h \
    utils/widgets/atleastonecheckedbuttongroup.h \
    utils/widgets/filenameeditwithbrowse.h \
    utils/models/otofilelistmodel.h \
    utils/widgets/otofileloadwidget.h \
    utils/widgets/otofilemultipleloadwidget.h \
    utils/widgets/otofilemultiplesavewidget.h \
    utils/widgets/otofilenameeditwithbrowse.h \
    utils/widgets/otofilesavewidget.h \
    utils/widgets/otofilesavewidgetabstract.h \
    utils/widgets/stringlistmodifywidget.h


FORMS += \
    RemoveAffix/removeaffixoptionwidget.ui \
    chain/chaintooloptionwidget.ui \
    cv_vcPartSplit/cv_vcpartsplitoptionwidget.ui \
    mainwindow.ui \
    overlapBatchSet/overlapbatchsetdialogoptionwidget.ui \
    toolBase/tooldialog.ui \
    removeDuplicate/removeduplicatedialogoptionwidget.ui \
    utils/dialogs/showdiffdialog.ui \
    utils/widgets/filenameeditwithbrowse.ui \
    utils/widgets/otofileloadwidget.ui \
    utils/widgets/otofilemultipleloadwidget.ui \
    utils/widgets/otofilemultiplesavewidget.ui \
    utils/widgets/otofilesavewidget.ui \
    utils/widgets/stringlistmodifywidget.ui

include(include.pri)
include(lib.pri)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    presets/overlap_start_preset/overlap_start_preset.qrc \
    resources/icon/icon.qrc

CONFIG(release, debug|release): DEFINES += NDEBUG

TRANSLATIONS += ../i18n/shine5402ototoolbox_en.ts

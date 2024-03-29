QT       += core gui concurrent network qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 file_copies

TARGET = KiraOtoToolbox

VERSION = 1.0.2

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
    chain/chaininvaliddialogadapter.cpp \
    chain/chainotolistmodifyworker.cpp \
    chain/chainstepsmodel.cpp \
    chain/chaintooloptionwidget.cpp \
    convertPlusMinusRight/convertplusminusrightdialogadapter.cpp \
    convertPlusMinusRight/convertplusminusrightoptionwidget.cpp \
    convertPlusMinusRight/convertplusminusrightotolistmodifyworker.cpp \
    copyOrReplaceByAlias/copyorreplacebyaliasdialogadapter.cpp \
    copyOrReplaceByAlias/copyorreplacebyaliasoptionwidget.cpp \
    copyOrReplaceByAlias/copyorreplacebyaliasotolistmodifyworker.cpp \
    jsScript/javascripttooldialogadapter.cpp \
    jsScript/javascripttooloptionwidget.cpp \
    jsScript/javascripttoolotolistmodifyworker.cpp \
    replaceFileName/filenamereplacemaptablemodel.cpp \
    replaceFileName/replacefilenameadapter.cpp \
    replaceFileName/replacefilenameoptionwidget.cpp \
    replaceFileName/replacefilenameotolistmodifyworker.cpp \
    toolBase/toolexception.cpp \
    utils/widgets/replacerule.cpp \
    utils/widgets/replacerulesdelegate.cpp \
    utils/widgets/replacerulesmodel.cpp \
    utils/widgets/replacerulesmultilineeditordialog.cpp \
    cv_vcPartSplit/cv_vcpartsplitoptionwidget.cpp \
    cv_vcPartSplit/cv_vcpartsplitotolistmodifyworker.cpp \
    cv_vcPartSplit/cv_vcpartsplittooldialogadapter.cpp \
    initFuncs.cpp \
    mergeOto/mergeotodialogadapter.cpp \
    mergeOto/mergeotooptionwidget.cpp \
    mergeOto/mergeotootolistmodifyworker.cpp \
    notdoanything/notdoanythingdialogadapter.cpp \
    notdoanything/notdoanythingoptionwidget.cpp \
    notdoanything/notdoanythingotolistmodifyworker.cpp \
    overlapBatchSet/overlapbatchsetotolistmodifyworker.cpp \
    preCenteredChangeValue/precenteredchangevalueadapter.cpp \
    preCenteredChangeValue/precenteredchangevalueoptionwidget.cpp \
    preCenteredChangeValue/precenteredchangevalueotolistmodifyworker.cpp \
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
    removeDuplicate/removeduplicatemoduleotolistmodifyworker.cpp \
    removeDuplicate/removeduplicateoptionwidget.cpp \
    removeDuplicate/removeduplicateotolistmodifyworker.cpp \
    removeSpecificEntries/removespecificentriesdialogadapter.cpp \
    removeSpecificEntries/removespecificentriesoptionwidget.cpp \
    removeSpecificEntries/removespecificentriesotolistmodifyworker.cpp \
    setAlias/setaliasdialogadapter.cpp \
    setAlias/setaliasoptionwidget.cpp \
    setAlias/setaliasotolistmodifyworker.cpp \
    tempoTransform/tempotransformoptionwidget.cpp \
    tempoTransform/tempotransformotolistmodifyworker.cpp \
    tempoTransform/tempotransfromdialogadapter.cpp \
    toolBase/optioncontainer.cpp \
    toolBase/otolistmodifyworker.cpp \
    toolBase/presetmanager.cpp \
    toolBase/presetwidgetcontainer.cpp \
    toolBase/tooldialog.cpp \
    toolBase/tooldialogadapter.cpp \
    toolBase/toolmanager.cpp \
    toolBase/tooloptionwidget.cpp \
    trimAroundSpecificValue/trimaroundspecificvaluedialogadapter.cpp \
    trimAroundSpecificValue/trimaroundspecificvalueoptionwidget.cpp \
    trimAroundSpecificValue/trimarounfspecificvalueotolistmodifyworker.cpp \
    utils/dialogs/showotolistdialog.cpp \
    utils/misc/misc.cpp \
    utils/models/otofilelistwithpreviousmodel.cpp \
    utils/models/otolistmodel.cpp \
    utils/models/otolistshowvaluechangemodel.cpp \
    utils/models/otofilelistmodel.cpp \
    utils/widgets/otofiledirectsavewidget.cpp \
    utils/widgets/otofileloadwidget.cpp \
    utils/widgets/otofilemultipleloadwidget.cpp \
    utils/widgets/otofilenameeditwithbrowse.cpp \
    utils/widgets/otofilesavewidget.cpp \
    utils/widgets/otofilesavewidgetabstract.cpp \
    utils/widgets/replaceruleswidget.cpp \
    vowelCrossfading/vowelcrossfadingdialogadapter.cpp \
    vowelCrossfading/vowelcrossfadingoptionwidget.cpp \
    vowelCrossfading/vowelcrossfadingotolistmodifyworker.cpp

HEADERS += \
    chain/chaindialogadapter.h \
    chain/chainelement.h \
    chain/chaininvaliddialogadapter.h \
    chain/chainotolistmodifyworker.h \
    chain/chainstepsmodel.h \
    chain/chaintooloptionwidget.h \
    convertPlusMinusRight/convertplusminusrightdialogadapter.h \
    convertPlusMinusRight/convertplusminusrightoptionwidget.h \
    convertPlusMinusRight/convertplusminusrightotolistmodifyworker.h \
    copyOrReplaceByAlias/copyorreplacebyaliasdialogadapter.h \
    copyOrReplaceByAlias/copyorreplacebyaliasoptionwidget.h \
    copyOrReplaceByAlias/copyorreplacebyaliasotolistmodifyworker.h \
    jsScript/javascripttooldialogadapter.h \
    jsScript/javascripttooloptionwidget.h \
    jsScript/javascripttoolotolistmodifyworker.h \
    replaceFileName/filenamereplacemaptablemodel.h \
    replaceFileName/replacefilenameadapter.h \
    replaceFileName/replacefilenameoptionwidget.h \
    replaceFileName/replacefilenameotolistmodifyworker.h \
    toolBase/toolexception.h \
    utils/widgets/replacerule.h \
    utils/widgets/replacerulesdelegate.h \
    utils/widgets/replacerulesmodel.h \
    utils/widgets/replacerulesmultilineeditordialog.h \
    cv_vcPartSplit/cv_vcpartsplitoptionwidget.h \
    cv_vcPartSplit/cv_vcpartsplitotolistmodifyworker.h \
    cv_vcPartSplit/cv_vcpartsplittooldialogadapter.h \
    initFuncs.h \
    mergeOto/mergeotodialogadapter.h \
    mergeOto/mergeotooptionwidget.h \
    mergeOto/mergeotootolistmodifyworker.h \
    notdoanything/notdoanythingdialogadapter.h \
    notdoanything/notdoanythingoptionwidget.h \
    notdoanything/notdoanythingotolistmodifyworker.h \
    overlapBatchSet/overlapbatchsetotolistmodifyworker.h \
    preCenteredChangeValue/precenteredchangevalueadapter.h \
    preCenteredChangeValue/precenteredchangevalueoptionwidget.h \
    preCenteredChangeValue/precenteredchangevalueotolistmodifyworker.h \
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
    removeDuplicate/removeduplicatemoduleotolistmodifyworker.h \
    removeDuplicate/removeduplicateoptionwidget.h \
    removeDuplicate/removeduplicateotolistmodifyworker.h \
    removeSpecificEntries/removespecificentriesdialogadapter.h \
    removeSpecificEntries/removespecificentriesoptionwidget.h \
    removeSpecificEntries/removespecificentriesotolistmodifyworker.h \
    setAlias/setaliasdialogadapter.h \
    setAlias/setaliasoptionwidget.h \
    setAlias/setaliasotolistmodifyworker.h \
    tempoTransform/tempotransformoptionwidget.h \
    tempoTransform/tempotransformotolistmodifyworker.h \
    tempoTransform/tempotransfromdialogadapter.h \
    toolBase/optioncontainer.h \
    toolBase/otolistmodifyworker.h \
    toolBase/presetmanager.h \
    toolBase/presetwidgetcontainer.h \
    toolBase/tooldialog.h \
    toolBase/tooldialogadapter.h \
    toolBase/toolmanager.h \
    toolBase/tooloptionwidget.h \
    trimAroundSpecificValue/trimaroundspecificvaluedialogadapter.h \
    trimAroundSpecificValue/trimaroundspecificvalueoptionwidget.h \
    trimAroundSpecificValue/trimarounfspecificvalueotolistmodifyworker.h \
    utils/dialogs/showotolistdialog.h \
    utils/misc/misc.h \
    utils/models/otofilelistwithpreviousmodel.h \
    utils/models/otolistmodel.h \
    utils/models/otolistshowvaluechangemodel.h \
    utils/models/otofilelistmodel.h \
    utils/widgets/otofiledirectsavewidget.h \
    utils/widgets/otofileloadwidget.h \
    utils/widgets/otofilemultipleloadwidget.h \
    utils/widgets/otofilenameeditwithbrowse.h \
    utils/widgets/otofilesavewidget.h \
    utils/widgets/otofilesavewidgetabstract.h \
    utils/widgets/replaceruleswidget.h \
    vowelCrossfading/vowelcrossfadingdialogadapter.h \
    vowelCrossfading/vowelcrossfadingoptionwidget.h \
    vowelCrossfading/vowelcrossfadingotolistmodifyworker.h


FORMS += \
    convertPlusMinusRight/convertplusminusrightoptionwidget.ui \
    copyOrReplaceByAlias/copyorreplacebyaliasoptionwidget.ui \
    jsScript/javascripttooloptionwidget.ui \
    replaceFileName/replacefilenameoptionwidget.ui \
    utils/widgets/replacerulesmultilineeditordialog.ui \
    mergeOto/mergeotooptionwidget.ui \
    preCenteredChangeValue/precenteredchangevalueoptionwidget.ui \
    removeAffix/removeaffixoptionwidget.ui \
    chain/chaintooloptionwidget.ui \
    cv_vcPartSplit/cv_vcpartsplitoptionwidget.ui \
    mainwindow.ui \
    overlapBatchSet/overlapbatchsetdialogoptionwidget.ui \
    removeDuplicate/removeduplicateoptionwidget.ui \
    removeSpecificEntries/removespecificentriesoptionwidget.ui \
    setAlias/setaliasoptionwidget.ui \
    tempoTransform/tempotransformoptionwidget.ui \
    toolBase/presetwidgetcontainer.ui \
    toolBase/tooldialog.ui \
    trimAroundSpecificValue/trimaroundspecificvalueoptionwidget.ui \
    utils/widgets/otofiledirectsavewidget.ui \
    utils/widgets/otofileloadwidget.ui \
    utils/widgets/otofilemultipleloadwidget.ui \
    utils/widgets/otofilesavewidget.ui \
    utils/widgets/replaceruleswidget.ui \
    vowelCrossfading/vowelcrossfadingoptionwidget.ui

include(lib.pri)
include(external-lib.pri)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/font/font.qrc \
    resources/icon/icon.qrc \
    resources/logo/logo.qrc \
    resources/presets/built-in_presets.qrc \
    resources/splashscr/splashscr.qrc

CONFIG(release, debug|release): DEFINES += NDEBUG

# For showing git info
# Refresh on qmake call
GIT_HASH="\\\"$$system(git -C \""$$_PRO_FILE_PWD_"\" rev-parse --short HEAD)\\\""
GIT_DESCRIBE="\\\"$$system(git -C \""$$_PRO_FILE_PWD_"\" describe --tags --dirty)\\\""
GIT_BRANCH="\\\"$$system(git -C \""$$_PRO_FILE_PWD_"\" rev-parse --abbrev-ref HEAD)\\\""
DEFINES += GIT_HASH=$$GIT_HASH GIT_BRANCH=$$GIT_BRANCH GIT_DESCRIBE=$$GIT_DESCRIBE

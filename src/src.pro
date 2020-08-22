QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = Shine5402OtoToolBox

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
    ../lib/diff-match-patch/diff_match_patch.cpp \
    overlapBatchSet/overlapbatchsetotolistmodifyworker.cpp \
    removeAffix/removeaffixdialogadapter.cpp \
    removeAffix/removeaffixoptionwidget.cpp \
    removeAffix/removeaffixotolistmodifyworker.cpp \
    removeAffix/removepitchaffixotolistmodifyworker.cpp \
    removeAffix/removespecificaffixotolistmodifyworker.cpp \
    addAffix/addaffixdialogadapter.cpp \
    addAffix/addaffixoptionwidget.cpp \
    addAffix/addaffixotolistmodifyworker.cpp \
    main.cpp \
    mainwindow.cpp \
    overlapBatchSet/overlapbatchsetdialogadapter.cpp \
    overlapBatchSet/overlapbatchsetdialogoptionwidget.cpp \
    removeDuplicate/removeduplicatedialogadapter.cpp \
    removeDuplicate/removeduplicatedialogoptionwidget.cpp \
    toolBase/otolistmodifyworker.cpp \
    toolBase/tooldialog.cpp \
    toolBase/tooldialogadapter.cpp \
    toolBase/tooloptions.cpp \
    toolBase/tooloptionwidget.cpp \
    utils/dialogs/showdiffdialog.cpp \
    utils/dialogs/showotolistdialog.cpp \
    utils/dialogs/tableviewdialog.cpp \
    utils/models/otolistmodel.cpp \
    utils/models/otolistshowvaluechangemodel.cpp \
    utils/widgets/atleastonecheckedbuttongroup.cpp \
    utils/widgets/filenameeditwithbrowse.cpp \
    utils/widgets/otofileloadwidget.cpp \
    utils/widgets/otofilenameeditwithbrowse.cpp \
    utils/widgets/otofilesavewidget.cpp \
    utils/widgets/stringlistmodifywidget.cpp


HEADERS += \
    ../lib/diff-match-patch/diff_match_patch.h \
    overlapBatchSet/overlapbatchsetotolistmodifyworker.h \
    removeAffix/removeaffixdialogadapter.h \
    removeAffix/removeaffixoptionwidget.h \
    removeAffix/removeaffixotolistmodifyworker.h \
    removeAffix/removepitchaffixotolistmodifyworker.h \
    removeAffix/removespecificaffixotolistmodifyworker.h \
    addAffix/addaffixdialogadapter.h \
    addAffix/addaffixoptionwidget.h \
    addAffix/addaffixotolistmodifyworker.h \
    mainwindow.h \
    overlapBatchSet/overlapbatchsetdialogadapter.h \
    overlapBatchSet/overlapbatchsetdialogoptionwidget.h \
    removeDuplicate/removeduplicatedialogadapter.h \
    removeDuplicate/removeduplicatedialogoptionwidget.h \
    toolBase/otolistmodifyworker.h \
    toolBase/tooldialog.h \
    toolBase/tooldialogadapter.h \
    toolBase/tooloptions.h \
    toolBase/tooloptionwidget.h \
    utils/dialogs/showdiffdialog.h \
    utils/dialogs/showotolistdialog.h \
    utils/dialogs/tableviewdialog.h \
    utils/models/otolistmodel.h \
    utils/models/otolistshowvaluechangemodel.h \
    utils/widgets/atleastonecheckedbuttongroup.h \
    utils/widgets/filenameeditwithbrowse.h \
    utils/widgets/otofileloadwidget.h \
    utils/widgets/otofilenameeditwithbrowse.h \
    utils/widgets/otofilesavewidget.h \
    utils/widgets/stringlistmodifywidget.h


FORMS += \
    RemoveAffix/removeaffixoptionwidget.ui \
    mainwindow.ui \
    overlapBatchSet/overlapbatchsetdialogoptionwidget.ui \
    overlapBatchSet/overlapsetdialog.ui \
    toolBase/tooldialog.ui \
    removeDuplicate/removeduplicatedialogoptionwidget.ui \
    utils/dialogs/showdiffdialog.ui \
    utils/widgets/filenameeditwithbrowse.ui \
    utils/widgets/otofileloadwidget.ui \
    utils/widgets/otofilesavewidget.ui \
    utils/widgets/stringlistmodifywidget.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(include.pri)

RESOURCES += \
    presets/overlap_start_preset/overlap_start_preset.qrc

CONFIG(release, debug|release): DEFINES += NDEBUG

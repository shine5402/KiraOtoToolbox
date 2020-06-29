QT       += core gui

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
    RemoveAffix/removeaffixoptionwidget.cpp \
    RemoveAffix/removeaffixotolisttask.cpp \
    RemoveAffix/removepitchaffixotolisttask.cpp \
    RemoveAffix/removespecificaffixotolisttask.cpp \
    addSuffix/addsuffixdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    overlapBatchSet/overlapbatchsetdialogadapter.cpp \
    overlapBatchSet/overlapbatchsetdialogoptionwidget.cpp \
    removeDuplicate/removeduplicatedialogadapter.cpp \
    removeDuplicate/removeduplicatedialogoptionwidget.cpp \
    toolBase/otolisttask.cpp \
    toolBase/tooldialog.cpp \
    toolBase/tooldialogadapter.cpp \
    toolBase/tooloptions.cpp \
    toolBase/tooloptionwidget.cpp \
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
    RemoveAffix/removeaffixoptionwidget.h \
    RemoveAffix/removeaffixotolisttask.h \
    RemoveAffix/removepitchaffixotolisttask.h \
    RemoveAffix/removespecificaffixotolisttask.h \
    addSuffix/addsuffixdialog.h \
    mainwindow.h \
    overlapBatchSet/overlapbatchsetdialogadapter.h \
    overlapBatchSet/overlapbatchsetdialogoptionwidget.h \
    removeDuplicate/removeduplicatedialogadapter.h \
    removeDuplicate/removeduplicatedialogoptionwidget.h \
    toolBase/otolisttask.h \
    toolBase/tooldialog.h \
    toolBase/tooldialogadapter.h \
    toolBase/tooloptions.h \
    toolBase/tooloptionwidget.h \
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
    addSuffix/addsuffixdialog.ui \
    mainwindow.ui \
    overlapBatchSet/overlapbatchsetdialogoptionwidget.ui \
    overlapBatchSet/overlapsetdialog.ui \
    toolBase/tooldialog.ui \
    removeDuplicate/removeduplicatedialogoptionwidget.ui \
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

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
    addSuffix/addsuffixdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    overlapBatchSet/overlapsetdialog.cpp \
    removeDuplicate/removeduplicatedialog.cpp \
    removeDuplicate/removeduplicatedialogoptionwidget.cpp \
    toolBase/tooldialogadapter.cpp \
    toolBase/tooloptionwidget.cpp \
    utils/dialogs/showotolistdialog.cpp \
    utils/models/otolistaliasshowchangemodel.cpp \
    utils/models/otolistmodel.cpp \
    utils/models/otolistoverlapshowchangemodel.cpp \
    utils/widgets/filenameeditwithbrowse.cpp \
    utils/widgets/otofileloadwidget.cpp \
    utils/widgets/otofilenameeditwithbrowse.cpp \
    utils/widgets/otofilesavewidget.cpp \
    utils/widgets/stringlistmodifywidget.cpp


HEADERS += \
    addSuffix/addsuffixdialog.h \
    mainwindow.h \
    overlapBatchSet/overlapsetdialog.h \
    removeDuplicate/removeduplicatedialog.h \
    removeDuplicate/removeduplicatedialogoptionwidget.h \
    toolBase/tooldialogadapter.h \
    toolBase/tooloptionwidget.h \
    utils/dialogs/showotolistdialog.h \
    utils/models/otolistaliasshowchangemodel.h \
    utils/models/otolistmodel.h \
    utils/models/otolistoverlapshowchangemodel.h \
    utils/widgets/filenameeditwithbrowse.h \
    utils/widgets/otofileloadwidget.h \
    utils/widgets/otofilenameeditwithbrowse.h \
    utils/widgets/otofilesavewidget.h \
    utils/widgets/stringlistmodifywidget.h


FORMS += \
    addSuffix/addsuffixdialog.ui \
    mainwindow.ui \
    overlapBatchSet/overlapsetdialog.ui \
    removeDuplicate/removeduplicatedialog.ui \
    removeDuplicate/removeduplicatedialogoptionwidget.ui \
    utils/dialogs/showotolistdialog.ui \
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

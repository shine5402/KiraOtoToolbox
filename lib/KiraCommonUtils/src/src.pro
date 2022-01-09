TEMPLATE = lib

QT += core gui widgets

TARGET = KiraCommonUtils

CONFIG += c++17 staticlib

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += include/ \
            ../lib/fplus/include/
DEPENDPATH += include/ \
            ../lib/fplus/include/

SOURCES += filesystem.cpp \
        dialogs/listviewdialog.cpp \
        dialogs/showhtmldialog.cpp \
        dialogs/tableviewdialog.cpp \
        i18n/translation.cpp \
        i18n/translationmanager.cpp \
        widgets/atleastonecheckedbuttongroup.cpp \
        widgets/dirnameeditwithbrowse.cpp \
        widgets/filenameeditwithbrowse.cpp \
        widgets/misc.cpp \
        widgets/stringlistmodifywidget.cpp \
        widgets/qballontip.cpp \
        stringfunc.cpp

HEADERS += include/kira/dialogs/listviewdialog.h \
        include/kira/dialogs/showhtmldialog.h \
        include/kira/dialogs/tableviewdialog.h \
        include/kira/i18n/translation.h \
        include/kira/i18n/translationmanager.h \
        include/kira/lib_helper/kfr_helper.h \
        include/kira/lib_helper/fplus_qt_adapter.h \
        include/kira/widgets/atleastonecheckedbuttongroup.h \
        include/kira/widgets/dirnameeditwithbrowse.h \
        include/kira/widgets/filenameeditwithbrowse.h \
        include/kira/widgets/misc.h \
        include/kira/widgets/stringlistmodifywidget.h \
        include/kira/base64.h \
        include/kira/filesystem.h \
        include/kira/setoperations.h \
        include/kira/widgets/qballontip.h \
        include/kira/stringfunc.h

FORMS += dialogs/showhtmldialog.ui \
         widgets/filenameeditwithbrowse.ui \
         widgets/stringlistmodifywidget.ui

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

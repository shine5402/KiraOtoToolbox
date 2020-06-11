QT += testlib
QT += gui core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_removeduplicatetest.cpp \
    ../../src/optionWidgets/removeduplicatedialogoptionwidget.cpp \
    ../../src/otolistaliasshowchangemodel.cpp \
    ../../src/otolistmodel.cpp \
    ../../src/removeduplicatedialog.cpp \
    ../../src/showotolistdialog.cpp \
    ../../src/widgets/filenameeditwithbrowse.cpp \
    ../../src/widgets/otofileloadwidget.cpp \
    ../../src/widgets/otofilenameeditwithbrowse.cpp \
    ../../src/widgets/otofilesavewidget.cpp \
    ../../src/widgets/stringlistmodifywidget.cpp

FORMS += \
    ../../src/optionWidgets/removeduplicatedialogoptionwidget.ui \
    ../../src/removeduplicatedialog.ui \
    ../../src/showotolistdialog.ui \
    ../../src/widgets/filenameeditwithbrowse.ui \
    ../../src/widgets/otofileloadwidget.ui \
    ../../src/widgets/otofilesavewidget.ui \
    ../../src/widgets/stringlistmodifywidget.ui

HEADERS += \
    ../../src/optionWidgets/removeduplicatedialogoptionwidget.h \
    ../../src/otolistaliasshowchangemodel.h \
    ../../src/otolistmodel.h \
    ../../src/removeduplicatedialog.h \
    ../../src/showotolistdialog.h \
    ../../src/widgets/filenameeditwithbrowse.h \
    ../../src/widgets/otofileloadwidget.h \
    ../../src/widgets/otofilenameeditwithbrowse.h \
    ../../src/widgets/otofilesavewidget.h \
    ../../src/widgets/stringlistmodifywidget.h

DEFINES += SHINE5402OTOBOX_TEST

INCLUDEPATH += ../../src/
DEPENDPATH += ../../src/

include(include.pri)

RESOURCES += \
    resources.qrc

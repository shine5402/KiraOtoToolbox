QT += testlib
QT += gui core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_removeduplicatetest.cpp \
    ../../src/otolistaliasshowchangemodel.cpp \
    ../../src/otolistmodel.cpp \
    ../../src/removeduplicatedialog.cpp \
    ../../src/showotolistdialog.cpp

FORMS += \
    ../../src/removeduplicatedialog.ui \
    ../../src/showotolistdialog.ui

HEADERS += \
    ../../src/otolistaliasshowchangemodel.h \
    ../../src/otolistmodel.h \
    ../../src/removeduplicatedialog.h \
    ../../src/showotolistdialog.h

DEFINES += SHINE5402OTOBOX_TEST

include(include.pri)

RESOURCES += \
    resources.qrc

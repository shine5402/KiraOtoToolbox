QT += testlib
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_utilwidgetstest.cpp \
    ../../src/utils/widgets/filenameeditwithbrowse.cpp \
    ../../src/utils/widgets/otofileloadwidget.cpp \
    ../../src/utils/widgets/otofilenameeditwithbrowse.cpp \
    ../../src/utils/widgets/otofilesavewidget.cpp \
    ../../src/utils/widgets/stringlistmodifywidget.cpp

FORMS += \
    ../../src/utils/widgets/filenameeditwithbrowse.ui \
    ../../src/utils/widgets/otofileloadwidget.ui \
    ../../src/utils/widgets/otofilesavewidget.ui \
    ../../src/utils/widgets/stringlistmodifywidget.ui

HEADERS += \
    ../../src/utils/widgets/filenameeditwithbrowse.h \
    ../../src/utils/widgets/otofileloadwidget.h \
    ../../src/utils/widgets/otofilenameeditwithbrowse.h \
    ../../src/utils/widgets/otofilesavewidget.h \
    ../../src/utils/widgets/stringlistmodifywidget.h

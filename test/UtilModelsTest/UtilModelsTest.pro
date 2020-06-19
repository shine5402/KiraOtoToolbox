QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_utilmodelstest.cpp \
    ../../src/utils/models/otolistmodel.cpp

include(include.pri)

HEADERS += \
    ../../src/utils/models/otolistmodel.h

INCLUDEPATH += ../../src/
DEPENDPATH += ../../src/

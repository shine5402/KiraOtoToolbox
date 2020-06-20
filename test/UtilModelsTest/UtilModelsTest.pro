QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_utilmodelstest.cpp \
    ../../src/utils/models/otolistmodel.cpp \
    ../../src/utils/models/otolistshowvaluechangemodel.cpp

include(include.pri)

HEADERS += \
    ../../src/utils/models/otolistmodel.h \
    ../../src/utils/models/otolistshowvaluechangemodel.h

INCLUDEPATH += ../../src/
DEPENDPATH += ../../src/

TEMPLATE = lib

QT += core gui

CONFIG += c++11 staticlib

HEADERS += include/qsourcehighliter.h \
           include/qsourcehighliterthemes.h \
           include/languagedata.h

SOURCES += qsourcehighliter.cpp \
    languagedata.cpp \
    qsourcehighliterthemes.cpp

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

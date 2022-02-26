TEMPLATE = lib

CONFIG += c++11 staticlib

INCLUDEPATH += .

DEPENDPATH += .

SOURCES += compact_enc_det/compact_enc_det.cc \
    compact_enc_det/compact_enc_det_hint_code.cc \
    util/encodings/encodings.cc \
    util/languages/languages.cc

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

*-g++ {
    QMAKE_CXXFLAGS += -Wno-narrowing
}

*-clang*{
    QMAKE_CXXFLAGS += -Wno-c++11-narrowing
}

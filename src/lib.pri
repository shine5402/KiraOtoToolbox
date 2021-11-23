INCLUDEPATH += ../lib/FunctionalPlus/include

SOURCES += ../lib/diff-match-patch/diff_match_patch.cpp \
    ../lib/misc/qballontip.cpp

HEADERS += ../lib/diff-match-patch/diff_match_patch.h \
    ../lib/misc/qballontip.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/KiraUTAUUtils/src/release/ -lKiraUTAUUtils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/KiraUTAUUtils/src/debug/ -lKiraUTAUUtils
else:unix: LIBS += -L$$OUT_PWD/../lib/KiraUTAUUtils/src/ -lKiraUTAUUtils

INCLUDEPATH += $$PWD/../lib/KiraUTAUUtils/src
DEPENDPATH += $$PWD/../lib/KiraUTAUUtils/src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/KiraUTAUUtils/src/release/libKiraUTAUUtils.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/KiraUTAUUtils/src/debug/libKiraUTAUUtils.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/KiraUTAUUtils/src/release/KiraUTAUUtils.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/KiraUTAUUtils/src/debug/KiraUTAUUtils.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/KiraUTAUUtils/src/libKiraUTAUUtils.a

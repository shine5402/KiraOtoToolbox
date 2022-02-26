# FunctionalPlus
INCLUDEPATH += ../lib/FunctionalPlus/include

# KiraUTAUUtils
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

# KiraCommonUtils
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/KiraCommonUtils/src/release/ -lKiraCommonUtils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/KiraCommonUtils/src/debug/ -lKiraCommonUtils
else:unix: LIBS += -L$$OUT_PWD/../lib/KiraCommonUtils/src/ -lKiraCommonUtils

INCLUDEPATH += $$PWD/../lib/KiraCommonUtils/src/include
DEPENDPATH += $$PWD/../lib/KiraCommonUtils/src/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/KiraCommonUtils/src/release/libKiraCommonUtils.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/KiraCommonUtils/src/debug/libKiraCommonUtils.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/KiraCommonUtils/src/release/KiraCommonUtils.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/KiraCommonUtils/src/debug/KiraCommonUtils.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/KiraCommonUtils/src/libKiraCommonUtils.a

# compact_enc_det
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/compact_enc_det/release/ -lcompact_enc_det
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/compact_enc_det/debug/ -lcompact_enc_det
else:unix: LIBS += -L$$OUT_PWD/../lib/compact_enc_det/ -lcompact_enc_det

INCLUDEPATH += $$PWD/../lib/compact_enc_det
DEPENDPATH += $$PWD/../lib/compact_enc_det

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/compact_enc_det/release/libcompact_enc_det.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/compact_enc_det/debug/libcompact_enc_det.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/compact_enc_det/release/compact_enc_det.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/compact_enc_det/debug/compact_enc_det.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/compact_enc_det/libcompact_enc_det.a

# QSourceHighlite

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/QSourceHighlite/release/ -lQSourceHighlite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/QSourceHighlite/debug/ -lQSourceHighlite
else:unix: LIBS += -L$$OUT_PWD/../lib/QSourceHighlite/ -lQSourceHighlite

INCLUDEPATH += $$PWD/../lib/QSourceHighlite/include
DEPENDPATH += $$PWD/../lib/QSourceHighlite/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/QSourceHighlite/release/libQSourceHighlite.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/QSourceHighlite/debug/libQSourceHighlite.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/QSourceHighlite/release/QSourceHighlite.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/QSourceHighlite/debug/QSourceHighlite.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/QSourceHighlite/libQSourceHighlite.a

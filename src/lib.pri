# FunctionalPlus
INCLUDEPATH += ../lib/FunctionalPlus/include


# 3rdparty includes (mapbox, diff-match-patch)
INCLUDEPATH += $$PWD/3rdparty

# compact_enc_det
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/compact_enc_det/release/ -lcompact_enc_det
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/compact_enc_det/debug/ -lcompact_enc_det
else:unix: LIBS += -L$$OUT_PWD/../lib/compact_enc_det/ -lcompact_enc_det

INCLUDEPATH += $$PWD/../lib/compact_enc_det
DEPENDPATH += $$PWD/../lib/compact_enc_det

win32*-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/compact_enc_det/release/libcompact_enc_det.a
else:win32*-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/compact_enc_det/debug/libcompact_enc_det.a
else:win32:!win32*-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/compact_enc_det/release/compact_enc_det.lib
else:win32:!win32*-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/compact_enc_det/debug/compact_enc_det.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/compact_enc_det/libcompact_enc_det.a

# QSourceHighlite

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/QSourceHighlite/release/ -lQSourceHighlite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/QSourceHighlite/debug/ -lQSourceHighlite
else:unix: LIBS += -L$$OUT_PWD/../lib/QSourceHighlite/ -lQSourceHighlite

INCLUDEPATH += $$PWD/../lib/QSourceHighlite/include
DEPENDPATH += $$PWD/../lib/QSourceHighlite/include

win328-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/QSourceHighlite/release/libQSourceHighlite.a
else:win32*-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/QSourceHighlite/debug/libQSourceHighlite.a
else:win32:!win32*-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/QSourceHighlite/release/QSourceHighlite.lib
else:win32:!win32*-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/QSourceHighlite/debug/QSourceHighlite.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/QSourceHighlite/libQSourceHighlite.a

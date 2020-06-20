# Put binary library include information here. It depends on your machine's settings.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../build-QtUTAULibrarys-Desktop_Qt_5_13_2_MinGW_32bit-Release/src/release/ -lQtUTAULibrarys
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build-QtUTAULibrarys-Desktop_Qt_5_13_2_MinGW_32bit-Debug/src/debug/ -lQtUTAULibrarysd
else:unix: LIBS += -L$$PWD/../../../src/build-QtUTAULibrarys-Desktop_Qt_5_13_2_MinGW_32bit-Debug/ -lQtUTAULibrarys

INCLUDEPATH += $$PWD/../../src/OtoUtil
DEPENDPATH += $$PWD/../../src/OtoUtil

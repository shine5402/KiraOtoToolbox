# Put binary library include information here. It depends on your machine's settings.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-QtUTAULibrarys-Desktop_Qt_5_13_2_MinGW_32_bit-Release/src/release/ -lQtUTAULibrarys
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-QtUTAULibrarys-Desktop_Qt_5_13_2_MinGW_32_bit-Debug/src/debug/ -lQtUTAULibrarysd

INCLUDEPATH += $$PWD/../../QtUTAULibrarys/src/OtoUtil
DEPENDPATH += $$PWD/../../QtUTAULibrarys/src/OtoUtil

# You need to specify extrernal not head-only libs in a "external-libs.pri" file to make this project work.
# QtCreator's "add lib" function would make your life easier, I guess.
# This project needs kfr to i/o/manipulate audio datas, you can find it here: https://www.kfrlib.com/

win32-clang-g++{
INCLUDEPATH += D:/kfr-master-install/mingw64-clang/include
DEPENDPATH += D:/kfr-master-install/mingw64-clang/include

win32: LIBS += -LD:/kfr-master-install/mingw64-clang/lib -lkfr_io -lkfr_dft

PRE_TARGETDEPS += D:/kfr-master-install/mingw64-clang/lib/libkfr_io.a \
                  D:/kfr-master-install/mingw64-clang/lib/libkfr_dft.a
}

win32-g++{
INCLUDEPATH += D:/kfr-master-install/mingw64-gcc/include
DEPENDPATH += D:/kfr-master-install/mingw64-gcc/include

win32: LIBS += -LD:/kfr-master-install/mingw64-gcc/lib -lkfr_io

PRE_TARGETDEPS += D:/kfr-master-install/mingw64-gcc/lib/libkfr_io.a
}


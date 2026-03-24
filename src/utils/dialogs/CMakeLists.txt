target_sources(KiraOtoToolbox PRIVATE
    listviewdialog.cpp listviewdialog.h
    showdiffdialog.cpp showdiffdialog.h showdiffdialog.ui
    commonhtmldialog.cpp commonhtmldialog.h commonhtmldialog.ui
    showotolistdialog.cpp showotolistdialog.h
    tableviewdialog.cpp tableviewdialog.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(KiraOtoToolbox PRIVATE
    listviewdialog.cpp listviewdialog.h
    showdiffdialog.cpp showdiffdialog.h showdiffdialog.ui
    showhtmldialog.cpp showhtmldialog.h showhtmldialog.ui
    showotolistdialog.cpp showotolistdialog.h
    tableviewdialog.cpp tableviewdialog.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

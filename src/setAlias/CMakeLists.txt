target_sources(KiraOtoToolbox PRIVATE
    setaliasdialogadapter.cpp setaliasdialogadapter.h
    setaliasoptionwidget.cpp setaliasoptionwidget.h setaliasoptionwidget.ui
    setaliasotolistmodifyworker.cpp setaliasotolistmodifyworker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

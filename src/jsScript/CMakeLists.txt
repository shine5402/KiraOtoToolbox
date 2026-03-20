target_sources(KiraOtoToolbox PRIVATE
    javascripttooldialogadapter.cpp javascripttooldialogadapter.h
    javascripttooloptionwidget.cpp javascripttooloptionwidget.h javascripttooloptionwidget.ui
    javascripttoolotolistmodifyworker.cpp javascripttoolotolistmodifyworker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

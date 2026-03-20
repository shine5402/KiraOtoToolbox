target_sources(KiraOtoToolbox PRIVATE
    mergeotodialogadapter.cpp mergeotodialogadapter.h
    mergeotooptionwidget.cpp mergeotooptionwidget.h mergeotooptionwidget.ui
    mergeotootolistmodifyworker.cpp mergeotootolistmodifyworker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

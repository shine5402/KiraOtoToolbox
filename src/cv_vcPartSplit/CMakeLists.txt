target_sources(KiraOtoToolbox PRIVATE
    cv_vcpartsplitoptionwidget.cpp cv_vcpartsplitoptionwidget.h cv_vcpartsplitoptionwidget.ui
    cv_vcpartsplitotolistmodifyworker.cpp cv_vcpartsplitotolistmodifyworker.h
    cv_vcpartsplittooldialogadapter.cpp cv_vcpartsplittooldialogadapter.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

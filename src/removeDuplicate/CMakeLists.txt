target_sources(KiraOtoToolbox PRIVATE
    orgnaizeduplicateotolistmodifyworker.cpp orgnaizeduplicateotolistmodifyworker.h
    removeduplicatedialogadapter.cpp removeduplicatedialogadapter.h
    removeduplicatemoduleotolistmodifyworker.cpp removeduplicatemoduleotolistmodifyworker.h
    removeduplicateoptionwidget.cpp removeduplicateoptionwidget.h removeduplicateoptionwidget.ui
    removeduplicateotolistmodifyworker.cpp removeduplicateotolistmodifyworker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(KiraOtoToolbox PRIVATE
    overlapbatchsetdialogadapter.cpp overlapbatchsetdialogadapter.h
    overlapbatchsetdialogoptionwidget.cpp overlapbatchsetdialogoptionwidget.h overlapbatchsetdialogoptionwidget.ui
    overlapbatchsetotolistmodifyworker.cpp overlapbatchsetotolistmodifyworker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

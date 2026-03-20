target_sources(KiraOtoToolbox PRIVATE
    filenamereplacemaptablemodel.cpp filenamereplacemaptablemodel.h
    replacefilenameadapter.cpp replacefilenameadapter.h
    replacefilenameoptionwidget.cpp replacefilenameoptionwidget.h replacefilenameoptionwidget.ui
    replacefilenameotolistmodifyworker.cpp replacefilenameotolistmodifyworker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

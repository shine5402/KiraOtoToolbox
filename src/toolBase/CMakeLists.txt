target_sources(KiraOtoToolbox PRIVATE
    optioncontainer.cpp optioncontainer.h
    otolistmodifyworker.cpp otolistmodifyworker.h
    presetmanager.cpp presetmanager.h
    presetwidgetcontainer.cpp presetwidgetcontainer.h presetwidgetcontainer.ui
    tooldialog.cpp tooldialog.h tooldialog.ui
    tooldialogadapter.cpp tooldialogadapter.h
    toolexception.cpp toolexception.h
    toolmanager.cpp toolmanager.h
    tooloptionwidget.cpp tooloptionwidget.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

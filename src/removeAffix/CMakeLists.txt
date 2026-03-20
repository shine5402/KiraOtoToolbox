target_sources(KiraOtoToolbox PRIVATE
    removeaffixdialogadapter.cpp removeaffixdialogadapter.h
    removeaffixoptionwidget.cpp removeaffixoptionwidget.h removeaffixoptionwidget.ui
    removeaffixotolistmodifyworker.cpp removeaffixotolistmodifyworker.h
    removedstringinfo.cpp removedstringinfo.h
    removepitchaffixotolistmodifyworker.cpp removepitchaffixotolistmodifyworker.h
    removespecificaffixotolistmodifyworker.cpp removespecificaffixotolistmodifyworker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

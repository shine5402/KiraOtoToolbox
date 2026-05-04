target_sources(KiraOtoToolbox PRIVATE
    JavaScriptToolDialogAdapter.cpp JavaScriptToolDialogAdapter.h
    JavaScriptToolOptionWidget.cpp JavaScriptToolOptionWidget.h JavaScriptToolOptionWidget.ui
    JavaScriptToolOtoListModifyWorker.cpp JavaScriptToolOtoListModifyWorker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

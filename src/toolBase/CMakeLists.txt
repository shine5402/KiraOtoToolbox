target_sources(KiraOtoToolbox PRIVATE
    OptionContainer.cpp OptionContainer.h
    OtoListModifyWorker.cpp OtoListModifyWorker.h
    PresetManager.cpp PresetManager.h
    PresetWidgetContainer.cpp PresetWidgetContainer.h PresetWidgetContainer.ui
    ToolDialog.cpp ToolDialog.h ToolDialog.ui
    ToolDialogAdapter.cpp ToolDialogAdapter.h
    ToolException.cpp ToolException.h
    ToolManager.cpp ToolManager.h
    ToolOptionWidget.cpp ToolOptionWidget.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

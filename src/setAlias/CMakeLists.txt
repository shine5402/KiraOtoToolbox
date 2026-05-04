target_sources(KiraOtoToolbox PRIVATE
    SetAliasDialogAdapter.cpp SetAliasDialogAdapter.h
    SetAliasOptionWidget.cpp SetAliasOptionWidget.h SetAliasOptionWidget.ui
    SetAliasOtoListModifyWorker.cpp SetAliasOtoListModifyWorker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

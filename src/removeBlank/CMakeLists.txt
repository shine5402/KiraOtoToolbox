target_sources(KiraOtoToolbox PRIVATE
    RemoveBlankDialogAdapter.cpp RemoveBlankDialogAdapter.h
    RemoveBlankOptionWidget.cpp RemoveBlankOptionWidget.h
    RemoveBlankOtoListModifyWorker.cpp RemoveBlankOtoListModifyWorker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

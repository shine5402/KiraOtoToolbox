target_sources(KiraOtoToolbox PRIVATE
    MergeOtoDialogAdapter.cpp MergeOtoDialogAdapter.h
    MergeOtoOptionWidget.cpp MergeOtoOptionWidget.h MergeOtoOptionWidget.ui
    MergeOtoOtoListModifyWorker.cpp MergeOtoOtoListModifyWorker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

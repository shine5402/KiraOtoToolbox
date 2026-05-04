target_sources(KiraOtoToolbox PRIVATE
    OverlapBatchSetDialogAdapter.cpp OverlapBatchSetDialogAdapter.h
    OverlapBatchSetDialogOptionWidget.cpp OverlapBatchSetDialogOptionWidget.h OverlapBatchSetDialogOptionWidget.ui
    OverlapBatchSetOtoListModifyWorker.cpp OverlapBatchSetOtoListModifyWorker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

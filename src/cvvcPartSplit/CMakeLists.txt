target_sources(KiraOtoToolbox PRIVATE
    CVVCPartSplitOptionWidget.cpp CVVCPartSplitOptionWidget.h CVVCPartSplitOptionWidget.ui
    CVVCPartSplitOtoListModifyWorker.cpp CVVCPartSplitOtoListModifyWorker.h
    CVVCPartSplitToolDialogAdapter.cpp CVVCPartSplitToolDialogAdapter.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

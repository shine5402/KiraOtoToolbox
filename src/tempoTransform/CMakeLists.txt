target_sources(KiraOtoToolbox PRIVATE
    TempoTransformOptionWidget.cpp TempoTransformOptionWidget.h TempoTransformOptionWidget.ui
    TempoTransformOtoListModifyWorker.cpp TempoTransformOtoListModifyWorker.h
    TempoTransformDialogAdapter.cpp TempoTransformDialogAdapter.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

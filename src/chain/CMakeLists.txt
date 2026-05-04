target_sources(KiraOtoToolbox PRIVATE
    ChainDialogAdapter.cpp ChainDialogAdapter.h
    ChainElement.h
    ChainInvalidDialogAdapter.cpp ChainInvalidDialogAdapter.h
    ChainOtoListModifyWorker.cpp ChainOtoListModifyWorker.h
    ChainStepsModel.cpp ChainStepsModel.h
    ChainToolOptionWidget.cpp ChainToolOptionWidget.h ChainToolOptionWidget.ui
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

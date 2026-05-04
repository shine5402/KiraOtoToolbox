target_sources(KiraOtoToolbox PRIVATE
    VowelCrossfadingDialogAdapter.cpp VowelCrossfadingDialogAdapter.h
    VowelCrossfadingOptionWidget.cpp VowelCrossfadingOptionWidget.h VowelCrossfadingOptionWidget.ui
    VowelCrossfadingOtoListModifyWorker.cpp VowelCrossfadingOtoListModifyWorker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

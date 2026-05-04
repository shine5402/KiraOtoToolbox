target_sources(KiraOtoToolbox PRIVATE
    RemoveAffixDialogAdapter.cpp RemoveAffixDialogAdapter.h
    RemoveAffixOptionWidget.cpp RemoveAffixOptionWidget.h RemoveAffixOptionWidget.ui
    RemoveAffixOtoListModifyWorker.cpp RemoveAffixOtoListModifyWorker.h
    RemovedStringInfo.cpp RemovedStringInfo.h
    RemovePitchAffixOtoListModifyWorker.cpp RemovePitchAffixOtoListModifyWorker.h
    RemoveSpecificAffixOtoListModifyWorker.cpp RemoveSpecificAffixOtoListModifyWorker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(KiraOtoToolbox PRIVATE
    OrganizeDuplicateOtoListModifyWorker.cpp OrganizeDuplicateOtoListModifyWorker.h
    RemoveDuplicateDialogAdapter.cpp RemoveDuplicateDialogAdapter.h
    RemoveDuplicateModuleOtoListModifyWorker.cpp RemoveDuplicateModuleOtoListModifyWorker.h
    RemoveDuplicateOptionWidget.cpp RemoveDuplicateOptionWidget.h RemoveDuplicateOptionWidget.ui
    RemoveDuplicateOtoListModifyWorker.cpp RemoveDuplicateOtoListModifyWorker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

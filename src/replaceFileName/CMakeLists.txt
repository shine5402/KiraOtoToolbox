target_sources(KiraOtoToolbox PRIVATE
    FileNameReplaceMapTableModel.cpp FileNameReplaceMapTableModel.h
    ReplaceFileNameAdapter.cpp ReplaceFileNameAdapter.h
    ReplaceFileNameOptionWidget.cpp ReplaceFileNameOptionWidget.h ReplaceFileNameOptionWidget.ui
    ReplaceFileNameOtoListModifyWorker.cpp ReplaceFileNameOtoListModifyWorker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

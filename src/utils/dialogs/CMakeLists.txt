target_sources(KiraOtoToolbox PRIVATE
    ListViewDialog.cpp ListViewDialog.h
    ShowDiffDialog.cpp ShowDiffDialog.h ShowDiffDialog.ui
    CommonHtmlDialog.cpp CommonHtmlDialog.h CommonHtmlDialog.ui
    ShowOtoListDialog.cpp ShowOtoListDialog.h
    TableViewDialog.cpp TableViewDialog.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

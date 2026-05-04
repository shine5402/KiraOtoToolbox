add_tool_test(test_replaceFileName
    tst_replaceFileName.cpp
    ${CMAKE_SOURCE_DIR}/src/replaceFileName/ReplaceFileNameOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/widgets/ReplaceRule.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/misc/MiscUtils.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/dialogs/TableViewDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/replaceFileName/FileNameReplaceMapTableModel.cpp
)


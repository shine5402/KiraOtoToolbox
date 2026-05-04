add_tool_test(test_cvvcPartSplit
    tst_cvvcPartSplit.cpp
    ${CMAKE_SOURCE_DIR}/src/cvvcPartSplit/CVVCPartSplitOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/misc/MiscUtils.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/misc/Misc.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/dialogs/ShowOtoListDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/dialogs/TableViewDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/dialogs/ShowDiffDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/models/OtoListModel.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/models/OtoListShowValueChangeModel.cpp
    ${CMAKE_SOURCE_DIR}/src/3rdparty/diff-match-patch/diff_match_patch.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

target_include_directories(test_cvvcPartSplit PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/FunctionalPlus/include
    ${CMAKE_SOURCE_DIR}/src/3rdparty/diff-match-patch
)
target_link_libraries(test_cvvcPartSplit PRIVATE compact_enc_det)

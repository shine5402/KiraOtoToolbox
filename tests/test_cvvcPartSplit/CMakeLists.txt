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
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

target_link_libraries(test_cvvcPartSplit PRIVATE dtl compact_enc_det)

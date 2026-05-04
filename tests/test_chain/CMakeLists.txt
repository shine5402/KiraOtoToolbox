add_tool_test(test_chain
    tst_chain.cpp
    ${CMAKE_SOURCE_DIR}/src/chain/ChainOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/notdoanything/NotDoAnythingDialogAdapter.cpp
    ${CMAKE_SOURCE_DIR}/src/notDoAnything/NotDoAnythingOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/notDoAnything/NotDoAnythingOptionWidget.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/ToolManager.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/ToolDialogAdapter.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/ToolException.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/ToolOptionWidget.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/PresetWidgetContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/PresetManager.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/dialogs/ShowDiffDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/dialogs/ShowOtoListDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/dialogs/TableViewDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/models/OtoListShowValueChangeModel.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/models/OtoListModel.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/widgets/Misc.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/widgets/QBalloonTip.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/i18n/TranslationManager.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/misc/MiscUtils.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/misc/Misc.cpp
    ${CMAKE_SOURCE_DIR}/src/3rdparty/diff-match-patch/diff_match_patch.cpp
)

target_include_directories(test_chain PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/FunctionalPlus/include
    ${CMAKE_SOURCE_DIR}/src/3rdparty/diff-match-patch
)
target_link_libraries(test_chain PRIVATE compact_enc_det)

add_tool_test(test_jsScript
    tst_jsScript.cpp
    ${CMAKE_SOURCE_DIR}/src/jsScript/JavaScriptToolOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/jsScript/JavaScriptToolDialogAdapter.cpp
    ${CMAKE_SOURCE_DIR}/src/jsScript/JavaScriptToolOptionWidget.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/misc/MiscUtils.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/misc/Misc.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/dialogs/CommonHtmlDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/widgets/RemoteImageTextBrowser.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/dialogs/TableViewDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/dialogs/ShowDiffDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/dialogs/ShowOtoListDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/models/OtoListModel.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/models/OtoListShowValueChangeModel.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/widgets/Misc.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/widgets/QBalloonTip.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/i18n/TranslationManager.cpp
    ${CMAKE_SOURCE_DIR}/src/replaceFileName/FileNameReplaceMapTableModel.cpp
    ${CMAKE_SOURCE_DIR}/src/3rdparty/diff-match-patch/diff_match_patch.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/ToolManager.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/ToolDialogAdapter.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/ToolException.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/ToolOptionWidget.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/PresetWidgetContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/PresetManager.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

target_include_directories(test_jsScript PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/FunctionalPlus/include
    ${CMAKE_SOURCE_DIR}/src/3rdparty/diff-match-patch
    ${CMAKE_SOURCE_DIR}/src/3rdparty
)
target_link_libraries(test_jsScript PRIVATE
    compact_enc_det
    QSourceHighlite
    kfr kfr_dsp kfr_io
    Qt6::Qml
)

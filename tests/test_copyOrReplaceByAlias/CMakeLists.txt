add_tool_test(test_copyOrReplaceByAlias
    tst_copyOrReplaceByAlias.cpp
    ${CMAKE_SOURCE_DIR}/src/copyOrReplaceByAlias/CopyOrReplaceByAliasOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/widgets/ReplaceRule.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/misc/MiscUtils.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)


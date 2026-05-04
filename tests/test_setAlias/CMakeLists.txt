add_tool_test(test_setAlias
    tst_setAlias.cpp
    ${CMAKE_SOURCE_DIR}/src/setAlias/SetAliasOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

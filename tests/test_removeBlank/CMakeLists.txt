add_tool_test(test_removeBlank
    tst_removeBlank.cpp
    ${CMAKE_SOURCE_DIR}/src/removeBlank/RemoveBlankOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

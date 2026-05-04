add_tool_test(test_removeDuplicate
    tst_removeDuplicate.cpp
    ${CMAKE_SOURCE_DIR}/src/removeDuplicate/RemoveDuplicateOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

add_tool_test(test_removeSpecificEntries
    tst_removeSpecificEntries.cpp
    ${CMAKE_SOURCE_DIR}/src/removeSpecificEntries/RemoveSpecificEntriesOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)


add_tool_test(test_removeSpecificEntries
    tst_removeSpecificEntries.cpp
    ${CMAKE_SOURCE_DIR}/src/removeSpecificEntries/RemoveSpecificEntriesOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

# fplus is header-only but needs include path
target_include_directories(test_removeSpecificEntries PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/FunctionalPlus/include
)

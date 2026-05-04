add_tool_test(test_trimAroundSpecificValue
    tst_trimAroundSpecificValue.cpp
    ${CMAKE_SOURCE_DIR}/src/trimAroundSpecificValue/TrimAroundSpecificValueOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

target_include_directories(test_trimAroundSpecificValue PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/FunctionalPlus/include
)

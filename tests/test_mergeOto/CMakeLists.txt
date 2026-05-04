add_tool_test(test_mergeOto
    tst_mergeOto.cpp
    ${CMAKE_SOURCE_DIR}/src/mergeOto/MergeOtoOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

target_include_directories(test_mergeOto PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/FunctionalPlus/include
)

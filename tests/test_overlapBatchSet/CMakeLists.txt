add_tool_test(test_overlapBatchSet
    tst_overlapBatchSet.cpp
    ${CMAKE_SOURCE_DIR}/src/overlapBatchSet/OverlapBatchSetOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

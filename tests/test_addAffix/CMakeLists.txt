add_tool_test(test_addAffix
    tst_addAffix.cpp
    ${CMAKE_SOURCE_DIR}/src/addAffix/AddAffixOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

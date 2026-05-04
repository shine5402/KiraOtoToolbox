add_tool_test(test_notDoAnything
    tst_notDoAnything.cpp
    ${CMAKE_SOURCE_DIR}/src/notDoAnything/NotDoAnythingOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

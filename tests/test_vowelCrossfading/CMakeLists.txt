add_tool_test(test_vowelCrossfading
    tst_vowelCrossfading.cpp
    ${CMAKE_SOURCE_DIR}/src/vowelCrossfading/VowelCrossfadingOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)


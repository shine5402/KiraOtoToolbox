add_tool_test(test_tempoTransform
    tst_tempoTransform.cpp
    ${CMAKE_SOURCE_DIR}/src/tempoTransform/TempoTransformOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

target_include_directories(test_tempoTransform PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/FunctionalPlus/include
)

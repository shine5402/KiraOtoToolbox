# Copy WAV fixture from sibling project (public domain LJ Speech)
set(FIXTURE_DIR ${CMAKE_CURRENT_BINARY_DIR}/fixtures)
file(MAKE_DIRECTORY ${FIXTURE_DIR})
configure_file(
    /Users/shine_5402/Project/KiraWavTar/tests/fixtures/LJ001-0001.wav
    ${FIXTURE_DIR}/LJ001-0001.wav
    COPYONLY
)

add_tool_test(test_convertPlusMinusRight
    tst_convertPlusMinusRight.cpp
    ${CMAKE_SOURCE_DIR}/src/convertPlusMinusRight/ConvertPlusMinusRightOtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/misc/MiscUtils.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OtoListModifyWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/toolBase/OptionContainer.cpp
    ${CMAKE_SOURCE_DIR}/src/otoUtils/OtoEntry.cpp
)

target_include_directories(test_convertPlusMinusRight PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/FunctionalPlus/include
    ${CMAKE_SOURCE_DIR}/src/3rdparty
)
target_link_libraries(test_convertPlusMinusRight PRIVATE kfr kfr_dsp kfr_io)
target_compile_definitions(test_convertPlusMinusRight PRIVATE
    FIXTURE_DIR="${FIXTURE_DIR}"
)

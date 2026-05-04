# --- Third-party libraries ---
# Note: compact_enc_det and QSourceHighlite currently live in
# ../../lib/ (git subtrees).

set(LIB_ROOT ${CMAKE_SOURCE_DIR}/lib)

# KFR (audio DSP library) — required
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/kfr/CMakeLists.txt)
    message(FATAL_ERROR "KFR submodule not found. Run: git submodule update --init src/3rdparty/kfr")
endif()
set(ENABLE_DFT ON CACHE BOOL "" FORCE)
set(KFR_ENABLE_DFT ON CACHE BOOL "" FORCE)
set(KFR_ENABLE_DSP ON CACHE BOOL "" FORCE)
set(KFR_INSTALL_HEADERS OFF CACHE BOOL "" FORCE)
set(KFR_INSTALL_LIBRARIES OFF CACHE BOOL "" FORCE)
set(ENABLE_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(kfr EXCLUDE_FROM_ALL)

# compact_enc_det (character encoding detection)
add_library(compact_enc_det STATIC
    ${LIB_ROOT}/compact_enc_det/compact_enc_det/compact_enc_det.cc
    ${LIB_ROOT}/compact_enc_det/compact_enc_det/compact_enc_det_hint_code.cc
    ${LIB_ROOT}/compact_enc_det/util/encodings/encodings.cc
    ${LIB_ROOT}/compact_enc_det/util/languages/languages.cc
)
target_include_directories(compact_enc_det PUBLIC ${LIB_ROOT}/compact_enc_det)
target_compile_options(compact_enc_det PRIVATE -Wno-c++11-narrowing)

# QSourceHighlite (syntax highlighting)
add_library(QSourceHighlite STATIC
    ${LIB_ROOT}/QSourceHighlite/qsourcehighliter.cpp
    ${LIB_ROOT}/QSourceHighlite/languagedata.cpp
    ${LIB_ROOT}/QSourceHighlite/qsourcehighliterthemes.cpp
)
target_include_directories(QSourceHighlite PUBLIC ${LIB_ROOT}/QSourceHighlite/include)
target_link_libraries(QSourceHighlite PRIVATE Qt6::Core Qt6::Gui)
set_target_properties(QSourceHighlite PROPERTIES AUTOMOC ON)

# diff-match-patch (text diff library)
add_library(diff_match_patch STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/diff-match-patch/diff_match_patch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/diff-match-patch/diff_match_patch.h
)
target_include_directories(diff_match_patch PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/diff-match-patch)
target_link_libraries(diff_match_patch PRIVATE Qt6::Core)

# mapbox/eternal.hpp (header-only compile-time map)
add_library(mapbox_eternal INTERFACE)
target_include_directories(mapbox_eternal INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

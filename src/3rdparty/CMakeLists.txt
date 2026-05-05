# --- Third-party libraries ---
# Note: compact_enc_det and QSourceHighlite currently live in
# ../../lib/ (git subtrees).

set(LIB_ROOT ${CMAKE_SOURCE_DIR}/lib)

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

# dtl (Diff Template Library) — header-only line diff
add_library(dtl INTERFACE)
target_include_directories(dtl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/dtl)

# dr_lib (dr_wav — WAV file reading)
add_library(dr_lib STATIC
    dr_libs/dr_wav.cpp
)
target_include_directories(dr_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

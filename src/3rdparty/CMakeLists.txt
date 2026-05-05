# --- Third-party libraries ---

# compact_enc_det (character encoding detection)
add_library(compact_enc_det STATIC
    compact_enc_det/compact_enc_det/compact_enc_det.cc
    compact_enc_det/compact_enc_det/compact_enc_det_hint_code.cc
    compact_enc_det/util/encodings/encodings.cc
    compact_enc_det/util/languages/languages.cc
)
target_include_directories(compact_enc_det PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/compact_enc_det)
target_compile_options(compact_enc_det PRIVATE -Wno-c++11-narrowing)

# QSourceHighlite (syntax highlighting)
add_library(QSourceHighlite STATIC
    QSourceHighlite/qsourcehighliter.cpp
    QSourceHighlite/languagedata.cpp
    QSourceHighlite/qsourcehighliterthemes.cpp
)
target_include_directories(QSourceHighlite PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/QSourceHighlite/include)
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

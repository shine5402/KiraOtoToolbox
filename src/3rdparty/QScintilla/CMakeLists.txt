# QScintilla 2.14.1 — built as a static library

set(QSCI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(QSCI_SCI ${CMAKE_CURRENT_SOURCE_DIR}/scintilla)

file(GLOB qscintilla_sources
    ${QSCI_SRC}/*.cpp
    ${QSCI_SCI}/src/*.cpp
    ${QSCI_SCI}/lexlib/*.cpp
    ${QSCI_SCI}/lexers/*.cpp
)
file(GLOB qscintilla_headers ${QSCI_SRC}/Qsci/*.h)

# macOS-only source
if(NOT APPLE)
    list(REMOVE_ITEM qscintilla_sources ${QSCI_SRC}/MacPasteboardMime.cpp)
endif()

add_library(qscintilla2 STATIC ${qscintilla_sources} ${qscintilla_headers})

target_include_directories(qscintilla2 PUBLIC
    ${QSCI_SRC}
    ${QSCI_SCI}/include
    ${QSCI_SCI}/lexlib
    ${QSCI_SCI}/src
)

target_compile_definitions(qscintilla2 PRIVATE
    SCINTILLA_QT
    SCI_LEXER
    INCLUDE_DEPRECATED_FEATURES
)

target_link_libraries(qscintilla2 PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::PrintSupport
)

set_target_properties(qscintilla2 PROPERTIES AUTOMOC ON AUTORCC OFF AUTOUIC OFF)

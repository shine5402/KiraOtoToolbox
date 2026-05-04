add_subdirectory(3rdparty)

qt_add_executable(KiraOtoToolbox
    main.cpp
    InitFuncs.cpp InitFuncs.h
    MainWindow.cpp MainWindow.h MainWindow.ui
)

# Add module subdirectories
# Each module manages its own source files via target_sources()
add_subdirectory(otoUtils)
add_subdirectory(toolBase)
add_subdirectory(utils)

# Tool subdirectories
add_subdirectory(addAffix)
add_subdirectory(chain)
add_subdirectory(convertPlusMinusRight)
add_subdirectory(copyOrReplaceByAlias)
add_subdirectory(cvvcPartSplit)
add_subdirectory(jsScript)
add_subdirectory(mergeOto)
add_subdirectory(notdoanything)
add_subdirectory(overlapBatchSet)
add_subdirectory(preCenteredChangeValue)
add_subdirectory(removeAffix)
add_subdirectory(removeBlank)
add_subdirectory(removeDuplicate)
add_subdirectory(removeSpecificEntries)
add_subdirectory(replaceFileName)
add_subdirectory(setAlias)
add_subdirectory(tempoTransform)
add_subdirectory(trimAroundSpecificValue)
add_subdirectory(vowelCrossfading)

# Root include directory for cross-module includes
target_include_directories(KiraOtoToolbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty
)

# Link libraries
target_link_libraries(KiraOtoToolbox PRIVATE
    Qt6::Core Qt6::Core5Compat Qt6::Gui Qt6::Widgets Qt6::Concurrent Qt6::Network Qt6::Qml Qt6::Svg
    compact_enc_det QSourceHighlite
    diff_match_patch mapbox_eternal
)

target_link_libraries(KiraOtoToolbox PRIVATE kfr kfr_dsp kfr_io)

# Resources
target_sources(KiraOtoToolbox PRIVATE
    ${CMAKE_SOURCE_DIR}/resources/font/font.qrc
    ${CMAKE_SOURCE_DIR}/resources/icon/icon.qrc
    ${CMAKE_SOURCE_DIR}/resources/logo/logo.qrc
    ${CMAKE_SOURCE_DIR}/resources/presets/built-in_presets.qrc
)

# Platform properties
set_target_properties(KiraOtoToolbox PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

if(WIN32)
    set_target_properties(KiraOtoToolbox PROPERTIES
        QT_TARGET_RC_ICONS ${CMAKE_SOURCE_DIR}/resources/icon/appIcon.ico
    )
endif()

if(APPLE)
    set(app_icon "${CMAKE_SOURCE_DIR}/resources/icon/appIcon.icns")
    target_sources(KiraOtoToolbox PRIVATE "${app_icon}")
    set_source_files_properties("${app_icon}" PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )
    set_target_properties(KiraOtoToolbox PROPERTIES
        MACOSX_BUNDLE_ICON_FILE "appIcon.icns"
        MACOSX_BUNDLE_GUI_IDENTIFIER "top.shine5402.KiraOtoToolbox"
    )
endif()

# --- Git info embedding ---
execute_process(
    COMMAND git rev-parse --short HEAD
    OUTPUT_VARIABLE GIT_HASH OUTPUT_STRIP_TRAILING_WHITESPACE
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    ERROR_QUIET
)
execute_process(
    COMMAND git describe --tags --dirty
    OUTPUT_VARIABLE GIT_DESCRIBE OUTPUT_STRIP_TRAILING_WHITESPACE
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    ERROR_QUIET
)
execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    OUTPUT_VARIABLE GIT_BRANCH OUTPUT_STRIP_TRAILING_WHITESPACE
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    ERROR_QUIET
)
target_compile_definitions(KiraOtoToolbox PRIVATE
    GIT_HASH="${GIT_HASH}"
    GIT_BRANCH="${GIT_BRANCH}"
    GIT_DESCRIBE="${GIT_DESCRIBE}"
)

# Release build defines
target_compile_definitions(KiraOtoToolbox PRIVATE
    $<$<CONFIG:Release>:NDEBUG>
    $<$<CONFIG:RelWithDebInfo>:NDEBUG>
    QT_DEPRECATED_WARNINGS
)

# --- Separate Debug Info (macOS, RelWithDebInfo) ---
if(APPLE AND OSX_SEPARATE_DEBUG_INFO AND CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_custom_command(TARGET KiraOtoToolbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_BUNDLE_DIR:KiraOtoToolbox>.dSYM/Contents/Resources/DWARF"
        COMMAND /usr/bin/dsymutil --flat
            -o "$<TARGET_BUNDLE_DIR:KiraOtoToolbox>.dSYM/Contents/Resources/DWARF/KiraOtoToolbox"
            "$<TARGET_FILE:KiraOtoToolbox>"
        COMMAND /usr/bin/strip -S "$<TARGET_FILE:KiraOtoToolbox>"
        COMMENT "Extracting dSYM and stripping KiraOtoToolbox"
        VERBATIM
    )
endif()

# Translations
qt_add_translations(KiraOtoToolbox
    TS_FILE_BASE KiraOtoToolbox
    TS_FILE_DIR ${CMAKE_SOURCE_DIR}/translations
    MERGE_QT_TRANSLATIONS
)

# --- Install & Deploy ---
option(KIRAOTOTOOLBOX_INSTALL "Enable install and deploy rules" ON)

if(KIRAOTOTOOLBOX_INSTALL)
    install(TARGETS KiraOtoToolbox
        BUNDLE  DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    qt_generate_deploy_app_script(
        TARGET KiraOtoToolbox
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
    install(SCRIPT ${deploy_script})
endif()

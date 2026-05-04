# Core utility files (absorbed from KiraCommonUtils)
target_sources(KiraOtoToolbox PRIVATE
    FileSystem.cpp FileSystem.h
    StringFunc.cpp StringFunc.h
    UpdateChecker.cpp UpdateChecker.h
    Base64.h
    SetOperations.h
)

# Subdirectories
add_subdirectory(dialogs)
add_subdirectory(i18n)
add_subdirectory(lib_helper)
add_subdirectory(misc)
add_subdirectory(models)
add_subdirectory(widgets)

target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

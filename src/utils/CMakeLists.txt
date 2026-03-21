# Core utility files (absorbed from KiraCommonUtils)
target_sources(KiraOtoToolbox PRIVATE
    filesystem.cpp filesystem.h
    stringfunc.cpp stringfunc.h
    updatechecker.cpp updatechecker.h
    base64.h
    setoperations.h
)

# Subdirectories
add_subdirectory(dialogs)
add_subdirectory(i18n)
add_subdirectory(lib_helper)
add_subdirectory(misc)
add_subdirectory(models)
add_subdirectory(widgets)

target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

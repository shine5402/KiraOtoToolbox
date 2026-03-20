target_sources(KiraOtoToolbox PRIVATE
    vowelcrossfadingdialogadapter.cpp vowelcrossfadingdialogadapter.h
    vowelcrossfadingoptionwidget.cpp vowelcrossfadingoptionwidget.h vowelcrossfadingoptionwidget.ui
    vowelcrossfadingotolistmodifyworker.cpp vowelcrossfadingotolistmodifyworker.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

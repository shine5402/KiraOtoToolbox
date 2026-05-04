target_sources(KiraOtoToolbox PRIVATE
    OtoFileListModel.cpp OtoFileListModel.h
    OtoFileListWithPreviousModel.cpp OtoFileListWithPreviousModel.h
    OtoListModel.cpp OtoListModel.h
    OtoListShowValueChangeModel.cpp OtoListShowValueChangeModel.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

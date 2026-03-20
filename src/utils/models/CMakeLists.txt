target_sources(KiraOtoToolbox PRIVATE
    otofilelistmodel.cpp otofilelistmodel.h
    otofilelistwithpreviousmodel.cpp otofilelistwithpreviousmodel.h
    otolistmodel.cpp otolistmodel.h
    otolistshowvaluechangemodel.cpp otolistshowvaluechangemodel.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

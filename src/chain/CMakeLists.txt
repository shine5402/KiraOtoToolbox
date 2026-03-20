target_sources(KiraOtoToolbox PRIVATE
    chaindialogadapter.cpp chaindialogadapter.h
    chainelement.h
    chaininvaliddialogadapter.cpp chaininvaliddialogadapter.h
    chainotolistmodifyworker.cpp chainotolistmodifyworker.h
    chainstepsmodel.cpp chainstepsmodel.h
    chaintooloptionwidget.cpp chaintooloptionwidget.h chaintooloptionwidget.ui
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

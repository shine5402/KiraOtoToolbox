target_sources(KiraOtoToolbox PRIVATE
    # Absorbed from KiraCommonUtils
    atleastonecheckedbuttongroup.cpp atleastonecheckedbuttongroup.h
    dirnameeditwithbrowse.cpp dirnameeditwithbrowse.h
    filenameeditwithbrowse.cpp filenameeditwithbrowse.h filenameeditwithbrowse.ui
    misc.cpp misc.h
    qballontip.cpp qballontip.h
    stringlistmodifywidget.cpp stringlistmodifywidget.h stringlistmodifywidget.ui
    # Original project widgets
    otofiledirectsavewidget.cpp otofiledirectsavewidget.h otofiledirectsavewidget.ui
    otofileloadwidget.cpp otofileloadwidget.h otofileloadwidget.ui
    otofilemultipleloadwidget.cpp otofilemultipleloadwidget.h otofilemultipleloadwidget.ui
    otofilenameeditwithbrowse.cpp otofilenameeditwithbrowse.h
    otofilesavewidget.cpp otofilesavewidget.h otofilesavewidget.ui
    otofilesavewidgetabstract.cpp otofilesavewidgetabstract.h
    replacerule.cpp replacerule.h
    replacerulesdelegate.cpp replacerulesdelegate.h
    replacerulesmodel.cpp replacerulesmodel.h
    replacerulesmultilineeditordialog.cpp replacerulesmultilineeditordialog.h replacerulesmultilineeditordialog.ui
    replaceruleswidget.cpp replaceruleswidget.h replaceruleswidget.ui
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

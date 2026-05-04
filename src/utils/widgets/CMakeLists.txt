target_sources(KiraOtoToolbox PRIVATE
    # Absorbed from KiraCommonUtils
    AtLeastOneCheckedButtonGroup.cpp AtLeastOneCheckedButtonGroup.h
    DirNameEditWithBrowse.cpp DirNameEditWithBrowse.h
    FileNameEditWithBrowse.cpp FileNameEditWithBrowse.h FileNameEditWithBrowse.ui
    Misc.cpp Misc.h
    QBalloonTip.cpp QBalloonTip.h
    StringListModifyWidget.cpp StringListModifyWidget.h StringListModifyWidget.ui
    # Original project widgets
    OtoFileDirectSaveWidget.cpp OtoFileDirectSaveWidget.h OtoFileDirectSaveWidget.ui
    OtoFileLoadWidget.cpp OtoFileLoadWidget.h OtoFileLoadWidget.ui
    OtoFileMultipleLoadWidget.cpp OtoFileMultipleLoadWidget.h OtoFileMultipleLoadWidget.ui
    OtoFileNameEditWithBrowse.cpp OtoFileNameEditWithBrowse.h
    OtoFileSaveWidget.cpp OtoFileSaveWidget.h OtoFileSaveWidget.ui
    OtoFileSaveWidgetAbstract.cpp OtoFileSaveWidgetAbstract.h
    ReplaceRule.cpp ReplaceRule.h
    ReplaceRulesDelegate.cpp ReplaceRulesDelegate.h
    ReplaceRulesModel.cpp ReplaceRulesModel.h
    ReplaceRulesMultilineEditorDialog.cpp ReplaceRulesMultilineEditorDialog.h ReplaceRulesMultilineEditorDialog.ui
    ReplaceRulesWidget.cpp ReplaceRulesWidget.h ReplaceRulesWidget.ui
    RemoteImageTextBrowser.cpp RemoteImageTextBrowser.h
    SvgWidget.cpp SvgWidget.h
)
target_include_directories(KiraOtoToolbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

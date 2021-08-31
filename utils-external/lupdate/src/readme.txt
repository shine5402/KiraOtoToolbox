A modified copy of lupdate tool from Qt's code (5.15.2), under GPL-3.0.
I modify this tool as I'm using some custom marcos, whose paramters need to be translated too.
Though lupdate.exe in Qt 6 toolchain has ability to use clang to parse, which provide functionality to take marco into thought, it still can not recognize a marco from include. It's kind of ugly to modify the pattern to use the custom macros (like DEFINE_TOOL_NAME(QT_TRANSLATE_NOOP("TOOL_NAME", tool_name))), so I just modify this tool.
This branch would take these marco to into thought:
  - REGISTER_TOOL(type, adapter_class), which will acts like QT_TRANSLATE_NOOP("TOOL_TYPE", type)
  - DEFINE_TOOL_NAME(name), which will acts like QT_TRANSLATE_NOOP("TOOL_NAME", type)

To use this tool, you need copy these utilities from Qt bin directory:
  - lupdate-pro.exe
  - lprodump.exe
  - qmake.exe
  - Qt5Core dynamic lib for your platform
  - mkspecs
You also write a file called qt.conf, and write like:

    [Paths]
    Prefix=[Path to where mkspecs go, can be relative, like "."]

And you can use it as Qt's bulit in version! I also put a verison of this for x64 Windows in this repo. Use it if you are using x64 Windows.

; Inno Setup script for KiraOtoToolbox
; Compile with: iscc scripts\installer-windows.iss

#define AppBinary "..\build\artifact\bin\KiraOtoToolbox.exe"

#ifndef AppVersion
  #if FileExists(AppBinary)
    #define AppVersion GetStringFileInfo(AppBinary, "ProductVersion")
    #define VersionInfoVersion GetVersionNumbersString(AppBinary)
  #else
    #define AppVersion "0.0.0"
    #define VersionInfoVersion "0.0.0.0"
  #endif
#endif

[Setup]
AppName=KiraOtoToolbox
AppVersion={#AppVersion}
AppPublisher=shine5402
AppPublisherURL=https://github.com/shine5402/KiraOtoToolbox
DefaultDirName={autopf}\KiraOtoToolbox
DefaultGroupName=KiraOtoToolbox
UninstallDisplayIcon={app}\bin\KiraOtoToolbox.exe
OutputDir=..\build
OutputBaseFilename=KiraOtoToolbox-{#AppVersion}-setup
SetupIconFile=..\resources\icon\appIcon.ico
LicenseFile=..\LICENSE
Compression=lzma2
SolidCompression=yes
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
WizardStyle=modern
VersionInfoVersion={#VersionInfoVersion}

[Files]
Source: "..\build\artifact\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\KiraOtoToolbox"; Filename: "{app}\bin\KiraOtoToolbox.exe"
Name: "{autodesktop}\KiraOtoToolbox"; Filename: "{app}\bin\KiraOtoToolbox.exe"; Tasks: desktopicon

[Languages]
Name: "en"; MessagesFile: "compiler:Default.isl"
Name: "zh_CN"; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Tasks]
Name: "desktopicon"; Description: "Create a &desktop shortcut"; GroupDescription: "Additional shortcuts:"

[Run]
Filename: "{app}\bin\KiraOtoToolbox.exe"; Description: "Launch KiraOtoToolbox"; Flags: nowait postinstall skipifsilent

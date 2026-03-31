#ifndef AppVersion
  #define AppVersion "0.1.0"
#endif

#ifndef OutputDirectory
  #if SourcePath == ""
    #define OutputDirectory "Output"
  #else
    #define OutputDirectory SourcePath + "\Output"
  #endif
#endif

#ifndef Vst3Path
  #error "Vst3Path must be defined. Example: ISCC /DVst3Path=\"C:\\path\\to\\Brickstortion.vst3\""
#endif

[Setup]
AppId={{5D1E4F2A-6C9E-4C2F-9D04-7F6D1D1E2B74}}
AppName=Brickstortion
AppVersion={#AppVersion}
AppPublisher=FycSss
AppPublisherURL=https://github.com/FycSss/BrickStortion
DefaultDirName={commoncf}\VST3\Brickstortion.vst3
DisableDirPage=yes
DisableProgramGroupPage=yes
PrivilegesRequired=admin
PrivilegesRequiredOverridesAllowed=none
ArchitecturesInstallIn64BitMode=x64
OutputDir={#OutputDirectory}
OutputBaseFilename=Brickstortion-Setup-{#AppVersion}
Compression=lzma2
SolidCompression=yes
WizardStyle=modern
Uninstallable=yes
ChangesEnvironment=false
SetupLogging=yes

[Files]
Source: "{#Vst3Path}\*"; DestDir: "{commoncf}\VST3\Brickstortion.vst3"; Flags: recursesubdirs createallsubdirs replaceunconditionally

[UninstallDelete]
Type: filesandordirs; Name: "{commoncf}\VST3\Brickstortion.vst3"

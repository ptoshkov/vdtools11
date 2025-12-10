;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

  !define APPNAME "VD Tools 11"
  !define SUBKEY "Software\${APPNAME}"
  !define EXENAME "vdtools11.exe"

  ;Name and file
  Name "${APPNAME}"
  OutFile "Install.exe"
  Unicode True

  ;Default installation folder
  InstallDir "$LOCALAPPDATA\${APPNAME}"

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

;--------------------------------
;On init callback

Function .onInit
  SetRegView 64
  ReadRegStr $0 HKCU "${SUBKEY}" ""

  ${If} "$0" != ""
    StrCpy $INSTDIR "$0"
  ${EndIf}
FunctionEnd

;--------------------------------
;Create auto startup shortcut

Function CreateAutoStartupShortcut
  CreateShortCut "$SMSTARTUP\${APPNAME}.lnk" "$INSTDIR\${EXENAME}"
FunctionEnd

;--------------------------------
;Skip directory selection if reinstalling

Function SkipDirectorySelection
  SetRegView 64
  ReadRegStr $0 HKCU "${SUBKEY}" ""

  ${If} "$0" != ""
    Abort
  ${EndIf}
FunctionEnd

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING
  !define MUI_FINISHPAGE_RUN
  !define MUI_FINISHPAGE_RUN_FUNCTION "CreateAutoStartupShortcut"
  !define MUI_FINISHPAGE_RUN_TEXT "Auto Startup"

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "..\LICENSE.txt"
  !define MUI_PAGE_CUSTOMFUNCTION_PRE "SkipDirectorySelection"
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Install"

  SetOutPath "$INSTDIR"

  ;ADD YOUR OWN FILES HERE...
  File "${EXENAME}"

  SetRegView 64
  ReadRegStr $0 HKCU "${SUBKEY}" ""

  ${If} "$0" == ""
    ;Store installation folder
    WriteRegStr HKCU "${SUBKEY}" "" $INSTDIR

    ;Store settings
    WriteRegDWORD HKCU "${SUBKEY}" "StartOnHomeFlag" 0
    WriteRegDWORD HKCU "${SUBKEY}" "JumpingFlag" 0
    WriteRegDWORD HKCU "${SUBKEY}" "DraggingFlag" 0
  ${EndIf}

  ;Show entry in Add/Remove Programs
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" \
                  "DisplayName" "${APPNAME}"
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" \
                  "UninstallString" "$\"$INSTDIR\Uninstall.exe$\""

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  ;Create start menu item
  CreateShortcut "$SMPROGRAMS\${APPNAME}.lnk" "$INSTDIR\${EXENAME}"

SectionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;Kill the app if it is running
  ExecWait "TaskKill /IM ${EXENAME} /F"

  ;ADD YOUR OWN FILES HERE...
  Delete "$INSTDIR\${EXENAME}"

  Delete "$INSTDIR\Uninstall.exe"

  RMDir "$INSTDIR"

  SetRegView 64
  DeleteRegKey HKCU "${SUBKEY}"
  DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"

  ;Delete start menu item
  Delete "$SMPROGRAMS\${APPNAME}.lnk"

  ;Delete Auto Startup Shortcut
  Delete "$SMSTARTUP\${APPNAME}.lnk"

SectionEnd

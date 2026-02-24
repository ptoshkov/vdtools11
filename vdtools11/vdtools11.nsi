;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

  !define BUILDDIR "build"
  !define APPNAME "VD Tools 11"
  !define SUBKEY "Software\${APPNAME}"
  !define EXENAME "vdtools11.exe"
  !define LNKNAME "${APPNAME}.lnk"
  !define INSTNAME "Install.exe"
  !define UINSTNAME "Uninstall.exe"
  !define STARTONHOMEFLAG "StartOnHomeFlag"
  !define JUMPINGFLAG "JumpingFlag"
  !define DRAGGINGFLAG "DraggingFlag"
  !define ADDREMOVELISTKEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"

  ;Name and file
  Name "${APPNAME}"
  OutFile "${BUILDDIR}\${INSTNAME}"
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
  CreateShortCut "$SMSTARTUP\${LNKNAME}" "$INSTDIR\${EXENAME}"
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
  File "${BUILDDIR}\${EXENAME}"

  SetRegView 64
  ReadRegStr $0 HKCU "${SUBKEY}" ""

  ${If} "$0" == ""
    ;Store installation folder if it's a new installation
    WriteRegStr HKCU "${SUBKEY}" "" $INSTDIR

    ;Store default values of settings if it's a new installation
    WriteRegDWORD HKCU "${SUBKEY}" "${STARTONHOMEFLAG}" 0
    WriteRegDWORD HKCU "${SUBKEY}" "${JUMPINGFLAG}" 0
    WriteRegDWORD HKCU "${SUBKEY}" "${DRAGGINGFLAG}" 0
  ${EndIf}

  ;Show entry in Add/Remove Programs
  WriteRegStr HKCU "${ADDREMOVELISTKEY}" \
                  "DisplayName" "${APPNAME}"
  WriteRegStr HKCU "${ADDREMOVELISTKEY}" \
                  "UninstallString" "$\"$INSTDIR\${UINSTNAME}$\""

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\${UINSTNAME}"

  ;Create start menu item
  CreateShortcut "$SMPROGRAMS\${LNKNAME}" "$INSTDIR\${EXENAME}"

SectionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;Kill the app if it is running
  ExecWait "TaskKill /IM ${EXENAME} /F"

  ;ADD YOUR OWN FILES HERE...
  Delete "$INSTDIR\${EXENAME}"

  Delete "$INSTDIR\${UINSTNAME}"

  RMDir "$INSTDIR"

  ;Delete registry keys
  SetRegView 64
  DeleteRegKey HKCU "${SUBKEY}"
  DeleteRegKey HKCU "${ADDREMOVELISTKEY}"

  ;Delete start menu item
  Delete "$SMPROGRAMS\${LNKNAME}"

  ;Delete Auto Startup Shortcut
  Delete "$SMSTARTUP\${LNKNAME}"

SectionEnd

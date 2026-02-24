@set BUILDDIR="build"
@set CLASSNAME="vdtools11"
@set WINDOWNAME="VDTOOLS11"
@set APPNAME="VD Tools 11"
@set EXENAME="%CLASSNAME%.exe"
@set INSTNAME="Install.exe"
@set UINSTNAME="Uninstall.exe"
@set STARTONHOMEFLAG="StartOnHomeFlag"
@set JUMPINGFLAG="JumpingFlag"
@set DRAGGINGFLAG="DraggingFlag"
@set NSINAME="%CLASSNAME%.nsi"

@echo Activating VS Dev CMD 64-bit
@call "%ProgramFiles(x86)%\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat" -arch=amd64
@call :checkStageSuccessful

@echo Compiling VD Tools 11
@if not exist %BUILDDIR% mkdir %BUILDDIR%
@cl /Fo%BUILDDIR%\ /O2 /EHsc /W4 /DUNICODE *.cpp^
 ole32.lib user32.lib shell32.lib dwmapi.lib advapi32.lib^
 /link /out:%BUILDDIR%\\%EXENAME%
@call :checkStageSuccessful

@echo Creating installer
@"%ProgramFiles(x86)%\NSIS\makensis.exe" %NSINAME%
@call :checkStageSuccessful

@pause
exit 0

:checkStageSuccessful
@if %ERRORLEVEL% NEQ 0 (
    pause
    exit 1
)
exit /b 0

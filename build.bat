@set REPODIR=%CD%
@set BUILDDIR=%REPODIR%\build
@set RESOURCESDIR=%REPODIR%\resources
@set CLASSNAME="vdtools11"
@set WINDOWNAME="VDTOOLS11"
@set APPNAME="VD Tools 11"
@set EXENAME="%CLASSNAME%.exe"
@set INSTNAME="Install.exe"
@set UINSTNAME="Uninstall.exe"
@set STARTONHOMEFLAG="StartOnHomeFlag"
@set JUMPINGFLAG="JumpingFlag"
@set DRAGGINGFLAG="DraggingFlag"
@set INSTALLERSDIR=%REPODIR%\installers
@set VDTOOLS11SDIR=%REPODIR%\vdtools11
@set RCNAME="%CLASSNAME%.rc"
@set RESNAME="%CLASSNAME%.res"
@set NSINAME="%CLASSNAME%.nsi"

@if not exist %BUILDDIR% mkdir %BUILDDIR%

@echo Activating VS Dev CMD 64-bit
@call "%ProgramFiles(x86)%\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat" -arch=amd64
@call :checkStageSuccessful

@echo Compiling VD Tools 11 resource file
@rc /fo %BUILDDIR%\\%RESNAME% %RESOURCESDIR%\\%RCNAME%
@call :checkStageSuccessful

@echo Compiling VD Tools 11
@cl /Fo%BUILDDIR%\ /O2 /EHsc /W4 /DUNICODE^
 /D_REPODIR=%REPODIR% /D_BUILDDIR=%BUILDDIR% /D_RESOURCESDIR=%RESOURCESDIR%^
 /D_CLASSNAME=%CLASSNAME% /D_WINDOWNAME=%WINDOWNAME%^
 /D_APPNAME=%APPNAME% /D_EXENAME=%EXENAME% /D_INSTNAME=%INSTNAME%^
 /D_UINSTNAME=%UINSTNAME% /D_STARTONHOMEFLAG=%STARTONHOMEFLAG%^
 /D_JUMPINGFLAG=%JUMPINGFLAG% /D_DRAGGINGFLAG=%DRAGGINGFLAG%^
 %VDTOOLS11SDIR%\\*.cpp^
 ole32.lib user32.lib shell32.lib dwmapi.lib advapi32.lib %BUILDDIR%\\%RESNAME%^
 /link /out:%BUILDDIR%\\%EXENAME%
@call :checkStageSuccessful

@echo Creating installer
@"%ProgramFiles(x86)%\NSIS\makensis.exe"^
 /D_REPODIR=%REPODIR% /D_BUILDDIR=%BUILDDIR% /D_RESOURCESDIR=%RESOURCESDIR%^
 /D_CLASSNAME=%CLASSNAME% /D_WINDOWNAME=%WINDOWNAME%^
 /D_APPNAME=%APPNAME% /D_EXENAME=%EXENAME% /D_INSTNAME=%INSTNAME%^
 /D_UINSTNAME=%UINSTNAME% /D_STARTONHOMEFLAG=%STARTONHOMEFLAG%^
 /D_JUMPINGFLAG=%JUMPINGFLAG% /D_DRAGGINGFLAG=%DRAGGINGFLAG%^
 %INSTALLERSDIR%\\%NSINAME%
@call :checkStageSuccessful

@pause
exit 0

:checkStageSuccessful
@if %ERRORLEVEL% NEQ 0 (
    pause
    exit 1
)
exit /b 0

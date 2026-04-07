@set REPODIR=%CD%
@set BUILDDIR=%REPODIR%\build
@set RESOURCESDIR=%REPODIR%\resources
@set CLASSNAME=vdtools11
@set WINDOWNAME=VDTOOLS11
@set APPNAME=VD Tools 11
@set EXENAME=%CLASSNAME%.exe
@set LOGNAME=%CLASSNAME%.log
@set INSTNAME=Install.exe
@set UINSTNAME=Uninstall.exe
@set MAJORVER=0
@set MINORVER=3
@set PATCHVER=0
@set STARTONHOMEFLAG=StartOnHomeFlag
@set JUMPINGFLAG=JumpingFlag
@set DRAGGINGFLAG=DraggingFlag
@set DEFINES=/D_REPODIR="%REPODIR%" /D_BUILDDIR="%BUILDDIR%" /D_RESOURCESDIR="%RESOURCESDIR%"^
 /D_CLASSNAME="%CLASSNAME%" /D_WINDOWNAME="%WINDOWNAME%" /D_APPNAME="%APPNAME%"^
 /D_EXENAME="%EXENAME%" /D_LOGNAME="%LOGNAME%"^
 /D_INSTNAME="%INSTNAME%" /D_UINSTNAME="%UINSTNAME%"^
 /D_MAJORVER="%MAJORVER%" /D_MINORVER="%MINORVER%" /D_PATCHVER="%PATCHVER%"^
 /D_STARTONHOMEFLAG="%STARTONHOMEFLAG%" /D_JUMPINGFLAG="%JUMPINGFLAG%" /D_DRAGGINGFLAG="%DRAGGINGFLAG%"

@set VSDEVCMD2022=%ProgramFiles(x86)%\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat
@set VSDEVCMD2026=%ProgramFiles(x86)%\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat
@set INSTALLERSDIR=%REPODIR%\installers
@set VDTOOLS11SDIR=%REPODIR%\vdtools11
@set LIBDIR=%REPODIR%\libraries
@set CPPLOGDIR=%LIBDIR%\cpplog
@set QADIR=%REPODIR%\qa
@set RCNAME=%CLASSNAME%.rc
@set RESNAME=%CLASSNAME%.res
@set NSINAME=%CLASSNAME%.nsi
@set ARCHNAME=Install.zip

@if not exist "%BUILDDIR%" mkdir "%BUILDDIR%"

@echo ################################## Activating VS Dev CMD 64-bit ##################################
@if exist "%VSDEVCMD2022%" set VSDEVCMD=%VSDEVCMD2022%
@if exist "%VSDEVCMD2026%" set VSDEVCMD=%VSDEVCMD2026%
@call "%VSDEVCMD%" -arch=amd64
@call :checkStageSuccessful

@echo ################################## Compiling VD Tools 11 resource file ##################################
@rc /fo "%BUILDDIR%\%RESNAME%" "%RESOURCESDIR%\%RCNAME%"
@call :checkStageSuccessful

@echo ################################## Compiling VD Tools 11 ##################################
@cl /Fo"%BUILDDIR%\\" /O2 /EHsc /W4 /I "%CPPLOGDIR%" /DUNICODE %DEFINES%^
 "%VDTOOLS11SDIR%\*.cpp" ole32.lib user32.lib shell32.lib dwmapi.lib advapi32.lib "%BUILDDIR%\%RESNAME%"^
 /link /out:"%BUILDDIR%\%EXENAME%"
@call :checkStageSuccessful

@echo ################################## Creating installer ##################################
@"%ProgramFiles(x86)%\NSIS\makensis.exe" %DEFINES% "%INSTALLERSDIR%\%NSINAME%"
@call :checkStageSuccessful

@echo ################################## Creating archive ##################################
tar -avcf "%BUILDDIR%\%ARCHNAME%" --directory "%BUILDDIR%" "%INSTNAME%"
@call :checkStageSuccessful

@echo ################################## Running unit tests ##################################
@cl /Fo"%BUILDDIR%\\" /Fe"%BUILDDIR%\\" /O2 /EHsc /W4 /I "%VDTOOLS11SDIR%" /wd4273 /DUNICODE %DEFINES% "%QADIR%\preftest.cpp"

:: Find all files in the build directory which match the expression "*test.exe"
:: and run them.
for %%f in ("%BUILDDIR%\*test.exe") do (
    %%f
)

@call :checkStageSuccessful

@pause
exit 0

:checkStageSuccessful
@if %ERRORLEVEL% NEQ 0 (
    pause
    exit 1
)
echo.
echo.
exit /b 0

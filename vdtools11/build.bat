@echo Activating VS Dev CMD 64-bit
@call "%ProgramFiles(x86)%\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat" -arch=amd64

@if %ERRORLEVEL% NEQ 0 (
    pause
    exit /b 1
)

@echo Compiling VD Tools 11
@cl /O2 /EHsc /W4 /DUNICODE *.cpp ole32.lib user32.lib shell32.lib dwmapi.lib advapi32.lib /link /out:vdtools11.exe

@if %ERRORLEVEL% NEQ 0 (
    pause
    exit /b 1
)

@echo Creating installer
@"%ProgramFiles(x86)%\NSIS\makensis.exe" vdtools11.nsi

@if %ERRORLEVEL% NEQ 0 (
    pause
    exit /b 1
)

@pause
exit /b 0

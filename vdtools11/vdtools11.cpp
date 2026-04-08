#include <windows.h>
#include <shobjidl.h>

#include "prop.h"
#include "log.h"
#include "co.h"
#include "ui.h"
#include "pref.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR /* pCmdLine */, int /* nCmdShow */)
{
    // Prevent multiple instances from running.
    if (FindWindow(CLASSNAME, WINDOWNAME))
    {
        MessageBox(NULL, TEXT("" APPNAME " is already running."), NULL, MB_ICONWARNING);
        return 1;
    }

    if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
    {
        logError(TEXT("Could not initialize COM."));
        return 1;
    }

    // log setup.
    logStart();

    // co setup.
    coCreateInstances();
    if (prefStartOnHomeChecked()) coJumpToDesktop(0, FALSE);

    // ui setup.
    uiJumpToDesktop = coJumpToDesktop;
    uiGetCurrentDesktop = coGetCurrentDesktop;
    uiStartOnHomeChecked = prefStartOnHomeChecked;
    uiJumpingChecked = prefJumpingChecked;
    uiDraggingChecked = prefDraggingChecked;
    uiNumberChecked = prefNumberChecked;
    uiToggleStartOnHome = prefToggleStartOnHome;
    uiToggleJumping = prefToggleJumping;
    uiToggleDragging = prefToggleDragging;
    uiToggleNumber = prefToggleNumber;
    uiSetInstance(hInstance);
    uiCreateWindow();
    uiAddTrayIcon();
    if (prefJumpingChecked()) uiRegisterJumpKeys();
    if (prefDraggingChecked()) uiRegisterDragKeys();
    if (prefNumberChecked()) uiHookWinEvents();

    uiStartMessageLoop();

    // co destroy.
    coReleaseInstances();

    // log destroy.
    logStop();

    CoUninitialize();

    return 0;
}

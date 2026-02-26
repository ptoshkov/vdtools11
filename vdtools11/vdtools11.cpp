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
        logError(TEXT("VD Tools 11 is already running."));
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
    uiToggleStartOnHome = prefToggleStartOnHome;
    uiToggleJumping = prefToggleJumping;
    uiToggleDragging = prefToggleDragging;
    uiSetInstance(hInstance);
    uiCreateWindow();
    uiAddTrayIcon();
    if (prefJumpingChecked()) uiRegisterJumpKeys();
    if (prefDraggingChecked()) uiRegisterDragKeys();

    uiStartMessageLoop();

    // co destroy.
    coReleaseInstances();

    // log destroy.
    logStop();

    CoUninitialize();

    return 0;
}

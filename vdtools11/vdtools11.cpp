#include <windows.h>
#include <shobjidl.h>

#include "co.h"
#include "ui.h"
#include "pref.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR /* pCmdLine */, int /* nCmdShow */)
{
    const WCHAR szClassName[] = TEXT("vdtools11");
    const WCHAR szWindowName[] = TEXT("VDTOOLS11");

    if (FindWindow(szClassName, szWindowName))
    {
        // Prevent multiple instances from running.
        MessageBox(NULL, TEXT("VD Tools 11 is already running."), TEXT("Error"), MB_OK);
        return 1;
    }

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    if (SUCCEEDED(hr))
    {
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
        uiCreateWindow(hInstance, szClassName, szWindowName);
        uiAddTrayIcon();
        if (prefJumpingChecked()) uiRegisterJumpKeys();
        if (prefDraggingChecked()) uiRegisterDragKeys();
        uiStartMessageLoop();

        // co destroy.
        coReleaseInstances();

        CoUninitialize();
    }
    else
    {
        MessageBox(NULL, TEXT("Could not initialize COM."), TEXT("Error"), MB_OK);
    }

    return 0;
}

#include <windows.h>
#include <shobjidl.h>

#include "co.h"
#include "ui.h"
#include "pref.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR /* pCmdLine */, int /* nCmdShow */)
{
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
        hr = uiCreateWindow(hInstance);

        if (SUCCEEDED(hr))
        {
            uiAddTrayIcon();
            if (prefJumpingChecked()) uiRegisterJumpKeys();
            if (prefDraggingChecked()) uiRegisterDragKeys();
            uiStartMessageLoop();
        }

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

#include <windows.h>
#include <shellapi.h>

#include "ui.h"

#define WM_USER_TRAYICON    (WM_USER + 1)
#define ID_TRAY_APP_ICON    (1002)
#define ID_MENU_ITEM1       (1003)
#define ID_MENU_ITEM2       (1004)
#define ID_MENU_ITEM3       (1005)
#define ID_MENU_ABOUT       (1006)
#define ID_MENU_HELP        (1007)
#define ID_MENU_EXIT        (1008)
#define ID_HOTKEY1          (1009)
#define ID_HOTKEY2          (1010)
#define ID_HOTKEY3          (1011)
#define ID_HOTKEY4          (1012)
#define ID_HOTKEY5          (1013)
#define ID_HOTKEY6          (1014)
#define ID_HOTKEY7          (1015)
#define ID_HOTKEY8          (1016)
#define ID_HOTKEY9          (1017)
#define ID_HOTKEY10         (1018)
#define ID_HOTKEY11         (1019)
#define ID_HOTKEY12         (1020)
#define ID_HOTKEY13         (1021)
#define ID_HOTKEY14         (1022)
#define ID_HOTKEY15         (1023)
#define ID_HOTKEY16         (1024)
#define ID_HOTKEY17         (1025)
#define ID_HOTKEY18         (1026)
#define ID_HOTKEY19         (1027)
#define ID_HOTKEY20         (1028)

void (*uiJumpToDesktop)(UINT, BOOL);
UINT (*uiGetCurrentDesktop)(void);
DWORD (*uiStartOnHomeChecked)(void);
DWORD (*uiJumpingChecked)(void);
DWORD (*uiDraggingChecked)(void);
void (*uiToggleStartOnHome)(void);
void (*uiToggleJumping)(void);
void (*uiToggleDragging)(void);
static HWND m_hWnd;
static NOTIFYICONDATA m_nid;
static UINT m_uTaskbarCreatedMsg;

void uiRegisterJumpKeys(void)
{
    if (m_hWnd)
    {
        UINT modifiers = (MOD_ALT | MOD_CONTROL | MOD_NOREPEAT | MOD_WIN);

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY1, modifiers, '1'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 1."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY2, modifiers, '2'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 2."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY3, modifiers, '3'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 3."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY4, modifiers, '4'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 4."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY5, modifiers, '5'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 5."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY6, modifiers, '6'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 6."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY7, modifiers, '7'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 7."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY8, modifiers, '8'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 8."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY9, modifiers, '9'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 9."), TEXT("Error"), MB_OK);
        }

        modifiers = (MOD_ALT | MOD_CONTROL | MOD_NOREPEAT | MOD_SHIFT | MOD_WIN);

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY10, modifiers, '1'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 10."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY11, modifiers, '2'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 11."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY12, modifiers, '3'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 12."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY13, modifiers, '4'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 13."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY14, modifiers, '5'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 14."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY15, modifiers, '6'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 15."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY16, modifiers, '7'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 16."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY17, modifiers, '8'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 17."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY18, modifiers, '9'))
        {
            MessageBox(NULL, TEXT("Could not register hot key 18."), TEXT("Error"), MB_OK);
        }
    }
}

void uiRegisterDragKeys(void)
{
    if (m_hWnd)
    {
        UINT modifiers = (MOD_ALT | MOD_CONTROL | MOD_NOREPEAT | MOD_WIN);

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY19, modifiers, VK_LEFT))
        {
            MessageBox(NULL, TEXT("Could not register hot key 19."), TEXT("Error"), MB_OK);
        }

        if (!RegisterHotKey(m_hWnd, ID_HOTKEY20, modifiers, VK_RIGHT))
        {
            MessageBox(NULL, TEXT("Could not register hot key 20."), TEXT("Error"), MB_OK);
        }
    }
}

void UnregisterJumpKeys(void)
{
    if (m_hWnd)
    {
        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY1))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 1."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY2))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 2."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY3))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 3."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY4))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 4."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY5))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 5."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY6))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 6."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY7))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 7."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY8))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 8."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY9))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 9."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY10))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 10."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY11))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 11."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY12))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 12."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY13))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 13."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY14))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 14."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY15))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 15."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY16))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 16."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY17))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 17."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY18))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 18."), TEXT("Error"), MB_OK);
        }
    }
}

void UnregisterDragKeys(void)
{
    if (m_hWnd)
    {
        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY19))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 19."), TEXT("Error"), MB_OK);
        }

        if (!UnregisterHotKey(m_hWnd, ID_HOTKEY20))
        {
            MessageBox(NULL, TEXT("Could not unregister hot key 20."), TEXT("Error"), MB_OK);
        }
    }
}

void ShowMenu(void)
{
    HMENU hMenu = CreatePopupMenu();

    if (hMenu)
    {
        AppendMenu(hMenu, MF_STRING | uiStartOnHomeChecked(), ID_MENU_ITEM1, TEXT("Switch To Desktop 1 On Start"));
        AppendMenu(hMenu, MF_STRING | uiJumpingChecked(), ID_MENU_ITEM2, TEXT("Jump To Desktop Using Shortcut"));
        AppendMenu(hMenu, MF_STRING | uiDraggingChecked(), ID_MENU_ITEM3, TEXT("Move Windows To Adjacent Desktop"));

        AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
        AppendMenu(hMenu, MF_STRING, ID_MENU_ABOUT, TEXT("About"));
        AppendMenu(hMenu, MF_STRING, ID_MENU_HELP, TEXT("Help"));
        AppendMenu(hMenu, MF_STRING, ID_MENU_EXIT, TEXT("Exit"));

        POINT pt;
        GetCursorPos(&pt);
        SetForegroundWindow(m_hWnd);
        BOOL ret = TrackPopupMenu(hMenu, TPM_LEFTBUTTON | TPM_RETURNCMD, pt.x, pt.y, 0, m_hWnd, NULL);

        DestroyMenu(hMenu);

        if (ID_MENU_ITEM1 == ret)
        {
            uiToggleStartOnHome();
        }

        if (ID_MENU_ITEM2 == ret)
        {
            uiToggleJumping();
            (uiJumpingChecked()) ? uiRegisterJumpKeys() : UnregisterJumpKeys();
        }

        if (ID_MENU_ITEM3 == ret)
        {
            uiToggleDragging();
            (uiDraggingChecked()) ? uiRegisterDragKeys() : UnregisterDragKeys();
        }

        if (ID_MENU_ABOUT == ret)
        {
            MessageBox(NULL, TEXT("VD Tools 11 v0.1.0 (commit 8a4542195bc3bdffdd97c00a138d672d9061775a)."), TEXT("About"), MB_OK);
        }

        if (ID_MENU_HELP == ret)
        {
            ShellExecute(NULL, TEXT("open"), TEXT("https://github.com/ptoshkov/vdtools11"), NULL, NULL, SW_SHOW);
        }

        if (ID_MENU_EXIT == ret)
        {
            DestroyWindow(m_hWnd);
        }
    }
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_USER_TRAYICON:
        switch (LOWORD(lParam))
        {
        case NIN_SELECT:
            ShowMenu();
            break;
        case WM_CONTEXTMENU:
            ShowMenu();
            break;
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_QUIT:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        Shell_NotifyIcon(NIM_DELETE, &m_nid);
        PostQuitMessage(0);
        return 0;
    }

    // Re-add the tray icon in case Windows Explorer restarts.
    if (m_uTaskbarCreatedMsg == uMsg)
    {
        uiAddTrayIcon();
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void uiCreateWindow(HINSTANCE hInstance, const WCHAR szClassName[], const WCHAR szWindowName[])
{
    m_hWnd = 0;
    m_uTaskbarCreatedMsg = 0;

    // Register the window class.
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = szClassName;
    RegisterClass(&wc);

    // Create hidden window.
    m_hWnd = CreateWindow(szClassName, szWindowName, 0,
        0, 0, 0, 0, NULL, NULL, hInstance, NULL);

    // Subscribe to taskbar created events in case Windows Explorer restarts.
    m_uTaskbarCreatedMsg = RegisterWindowMessage(TEXT("TaskbarCreated"));
}

void uiAddTrayIcon(void)
{
    if (m_hWnd)
    {
        // Add tray icon.
        m_nid.cbSize = sizeof(NOTIFYICONDATA);
        m_nid.hWnd = m_hWnd;
        m_nid.uID = ID_TRAY_APP_ICON;
        m_nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP;
        m_nid.uCallbackMessage = WM_USER_TRAYICON;
        m_nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        lstrcpy(m_nid.szTip, TEXT("VD Tools 11"));
        Shell_NotifyIcon(NIM_ADD, &m_nid);

        // NOTIFYICON_VERSION_4 is prefered
        m_nid.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIcon(NIM_SETVERSION, &m_nid);
    }
}

void uiStartMessageLoop(void)
{
    MSG msg;
    UINT idx;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        switch (msg.message)
        {
        case WM_HOTKEY:
            switch (msg.wParam)
            {
            case ID_HOTKEY1:
                uiJumpToDesktop(0, FALSE);
                break;
            case ID_HOTKEY2:
                uiJumpToDesktop(1, FALSE);
                break;
            case ID_HOTKEY3:
                uiJumpToDesktop(2, FALSE);
                break;
            case ID_HOTKEY4:
                uiJumpToDesktop(3, FALSE);
                break;
            case ID_HOTKEY5:
                uiJumpToDesktop(4, FALSE);
                break;
            case ID_HOTKEY6:
                uiJumpToDesktop(5, FALSE);
                break;
            case ID_HOTKEY7:
                uiJumpToDesktop(6, FALSE);
                break;
            case ID_HOTKEY8:
                uiJumpToDesktop(7, FALSE);
                break;
            case ID_HOTKEY9:
                uiJumpToDesktop(8, FALSE);
                break;
            case ID_HOTKEY10:
                uiJumpToDesktop(0, TRUE);
                break;
            case ID_HOTKEY11:
                uiJumpToDesktop(1, TRUE);
                break;
            case ID_HOTKEY12:
                uiJumpToDesktop(2, TRUE);
                break;
            case ID_HOTKEY13:
                uiJumpToDesktop(3, TRUE);
                break;
            case ID_HOTKEY14:
                uiJumpToDesktop(4, TRUE);
                break;
            case ID_HOTKEY15:
                uiJumpToDesktop(5, TRUE);
                break;
            case ID_HOTKEY16:
                uiJumpToDesktop(6, TRUE);
                break;
            case ID_HOTKEY17:
                uiJumpToDesktop(7, TRUE);
                break;
            case ID_HOTKEY18:
                uiJumpToDesktop(8, TRUE);
                break;
            case ID_HOTKEY19:
                idx = uiGetCurrentDesktop();
                uiJumpToDesktop(idx - 1, TRUE);
                break;
            case ID_HOTKEY20:
                idx = uiGetCurrentDesktop();
                uiJumpToDesktop(idx + 1, TRUE);
                break;
            }
            break;
        default:
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}


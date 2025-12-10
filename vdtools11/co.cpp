#include <windows.h>
#include <shobjidl.h>
#include <dwmapi.h>

#include "co.h"

const CLSID CLSID_ImmersiveShell =
    {0xC2F03A33, 0x21F5, 0x47FA, 0xB4, 0xBB, 0x15, 0x63, 0x62, 0xA2, 0xF2, 0x39};

const CLSID CLSID_VirtualDesktopManagerInternal =
    {0xC5E0CDCA, 0x7B6E, 0x41B2, 0x9F, 0xC4, 0xD9, 0x39, 0x75, 0xCC, 0x46, 0x7B};

MIDL_INTERFACE("3F07F4BE-B107-441A-AF0F-39D82529072C")
IVirtualDesktop : public IUnknown
{
public:
};

MIDL_INTERFACE("53F5CA0B-158F-4124-900C-057158060B27")
IVirtualDesktopManagerInternal : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE GetCount(
        UINT *pCount) = 0;

    virtual HRESULT STDMETHODCALLTYPE MoveViewToDesktop(
        /* IApplicationView */void *pView,
        IVirtualDesktop *pDesktop) = 0;

    virtual HRESULT STDMETHODCALLTYPE CanViewMoveDesktops(
        /* IApplicationView */void *pView,
        int *pfCanViewMoveDesktops) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetCurrentDesktop(
        IVirtualDesktop **ppDesktop) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetDesktops(
        IObjectArray **ppDesktops) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetAdjacentDesktop(
        IVirtualDesktop *pDesktopReference,
        /* AdjacentDesktop */int uDirection,
        IVirtualDesktop **ppAdjacentDesktop) = 0;

    virtual HRESULT STDMETHODCALLTYPE SwitchDesktop(
        IVirtualDesktop *pDesktop) = 0;

    virtual HRESULT STDMETHODCALLTYPE SwitchDesktopAndMoveForegroundView(
        IVirtualDesktop *pDesktop) = 0;
};

static IVirtualDesktopManager *m_pVirtualDesktopManager;
static IServiceProvider *m_pServiceProvider;
static IVirtualDesktopManagerInternal *m_pVirtualDesktopManagerInternal;
static DWORD m_lastJumpTimeMs;

void coCreateInstances(void)
{
    m_pVirtualDesktopManager = NULL;
    m_pServiceProvider = NULL;
    m_pVirtualDesktopManagerInternal = NULL;
    m_lastJumpTimeMs = 0;

    HRESULT hr = CoCreateInstance(CLSID_VirtualDesktopManager, NULL, CLSCTX_ALL,
        IID_PPV_ARGS(&m_pVirtualDesktopManager));

    if (SUCCEEDED(hr))
    {
        hr = CoCreateInstance(CLSID_ImmersiveShell, NULL, CLSCTX_ALL,
            IID_PPV_ARGS(&m_pServiceProvider));

        if (SUCCEEDED(hr))
        {
            hr = m_pServiceProvider->QueryService(CLSID_VirtualDesktopManagerInternal,
                &m_pVirtualDesktopManagerInternal);

            if (SUCCEEDED(hr))
            {}
            else
            {
                MessageBox(NULL, TEXT("Could not create Virtual Desktop Manager Internal object."), TEXT("Error"), MB_OK);
            }
        }
        else
        {
            MessageBox(NULL, TEXT("Could not create Service Provider object."), TEXT("Error"), MB_OK);
        }
    }
    else
    {
        MessageBox(NULL, TEXT("Could not create Virtual Desktop Manager object."), TEXT("Error"), MB_OK);
    }
}

void coReleaseInstances(void)
{
    if (m_pVirtualDesktopManager)
    {
        m_pVirtualDesktopManager->Release();
    }

    if (m_pServiceProvider)
    {
        m_pServiceProvider->Release();
    }

    if (m_pVirtualDesktopManagerInternal)
    {
        m_pVirtualDesktopManagerInternal->Release();
    }
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    if (!IsWindowVisible(hWnd))
    {
        return TRUE;
    }

    INT cloaked;
    DwmGetWindowAttribute(hWnd, DWMWA_CLOAKED, &cloaked, sizeof(INT));

    if (cloaked)
    {
        return TRUE;
    }

    WCHAR buf[3];
    int len = GetWindowText(hWnd, buf, 2);

    if (0 == len)
    {
        return TRUE;
    }

    IVirtualDesktopManager *pVirtualDesktopManager = reinterpret_cast<IVirtualDesktopManager*>(lParam);
    BOOL ret;
    pVirtualDesktopManager->IsWindowOnCurrentVirtualDesktop(hWnd, &ret);

    if (!ret)
    {
        return TRUE;
    }

    (void)SetForegroundWindow(hWnd);

    // Stop flashing the window.
    FLASHWINFO fwi = {0};
    fwi.cbSize = sizeof(fwi);
    fwi.hwnd = hWnd;
    fwi.dwFlags = FLASHW_STOP;
    fwi.uCount = 0;
    fwi.dwTimeout = 0;
    (void)FlashWindowEx(&fwi);

    return FALSE;
}

void coJumpToDesktop(UINT idx, BOOL bMoveForegroundView)
{
    const DWORD animationTimeoutMs = 200;
    DWORD currentTimeMs = GetTickCount();

    if ((currentTimeMs - m_lastJumpTimeMs) > animationTimeoutMs)
    {
        m_lastJumpTimeMs = currentTimeMs;

        IObjectArray *pDesktops;
        (void)m_pVirtualDesktopManagerInternal->GetDesktops(&pDesktops);

        UINT cnt;
        (void)pDesktops->GetCount(&cnt);

        if (idx < cnt)
        {
            IVirtualDesktop *pVirtualDesktop;
            pDesktops->GetAt(idx, IID_PPV_ARGS(&pVirtualDesktop));

            if (bMoveForegroundView)
            {
                (void)m_pVirtualDesktopManagerInternal->SwitchDesktopAndMoveForegroundView(pVirtualDesktop);
            }
            else
            {
                (void)m_pVirtualDesktopManagerInternal->SwitchDesktop(pVirtualDesktop);

                // Set the focus to a window in the new virtual desktop.
                EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(m_pVirtualDesktopManager));
            }
        }
    }
}

UINT coGetCurrentDesktop(void)
{
    IObjectArray *pDesktops;
    (void)m_pVirtualDesktopManagerInternal->GetDesktops(&pDesktops);

    UINT cnt;
    (void)pDesktops->GetCount(&cnt);

    IVirtualDesktop *pCurrentDesktop;
    (void)m_pVirtualDesktopManagerInternal->GetCurrentDesktop(&pCurrentDesktop);

    UINT idx;
    for (idx = 0; idx < cnt; idx++)
    {
        IVirtualDesktop *pVirtualDesktop;
        pDesktops->GetAt(idx, IID_PPV_ARGS(&pVirtualDesktop));

        if (pVirtualDesktop == pCurrentDesktop)
        {
            break;
        }
    }

    return idx;
}

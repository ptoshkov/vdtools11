#include <windows.h>
#include <shobjidl.h>
#include <dwmapi.h>

#include "co.h"
#include "log.h"

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

void coCreateInstances(void)
{
    m_pVirtualDesktopManager = NULL;
    m_pServiceProvider = NULL;
    m_pVirtualDesktopManagerInternal = NULL;

    HRESULT hr = CoCreateInstance(CLSID_VirtualDesktopManager, NULL, CLSCTX_ALL,
        IID_PPV_ARGS(&m_pVirtualDesktopManager));

    if (FAILED(hr))
    {
        logError(TEXT("Could not create Virtual Desktop Manager object."));
        return;
    }

    hr = CoCreateInstance(CLSID_ImmersiveShell, NULL, CLSCTX_ALL,
        IID_PPV_ARGS(&m_pServiceProvider));

    if (FAILED(hr))
    {
        logError(TEXT("Could not create Service Provider object."));
        return;
    }

    hr = m_pServiceProvider->QueryService(CLSID_VirtualDesktopManagerInternal,
        &m_pVirtualDesktopManagerInternal);

    if (FAILED(hr))
    {
        logError(TEXT("Could not create Virtual Desktop Manager Internal object."));
        return;
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

void coJumpToDesktop(UINT idx, BOOL bMoveForegroundView)
{
    if ((NULL == m_pVirtualDesktopManager) || (NULL == m_pVirtualDesktopManagerInternal))
    {
        return;
    }

    IObjectArray *pDesktops;
    (void)m_pVirtualDesktopManagerInternal->GetDesktops(&pDesktops);

    UINT cnt;
    (void)pDesktops->GetCount(&cnt);

    if (idx >= cnt)
    {
        return;
    }

    IVirtualDesktop *pVirtualDesktop;
    pDesktops->GetAt(idx, IID_PPV_ARGS(&pVirtualDesktop));

    IVirtualDesktop *pCurrentDesktop;
    (void)m_pVirtualDesktopManagerInternal->GetCurrentDesktop(&pCurrentDesktop);

    if (pCurrentDesktop == pVirtualDesktop)
    {
        return;
    }

    if (bMoveForegroundView)
    {
        (void)m_pVirtualDesktopManagerInternal->SwitchDesktopAndMoveForegroundView(pVirtualDesktop);
    }
    else
    {
        // Set the progman.exe window as the foreground window, otherwise Windows
        // will not be able to focus a window in the new virtual desktop after switching.
        HWND hWnd = FindWindow(TEXT("Progman"), NULL);
        SetForegroundWindow(hWnd);
        (void)m_pVirtualDesktopManagerInternal->SwitchDesktop(pVirtualDesktop);
    }
}

UINT coGetCurrentDesktop(void)
{
    UINT idx = 0;

    if (NULL == m_pVirtualDesktopManagerInternal)
    {
        return idx;
    }

    IObjectArray *pDesktops;
    (void)m_pVirtualDesktopManagerInternal->GetDesktops(&pDesktops);

    UINT cnt;
    (void)pDesktops->GetCount(&cnt);

    IVirtualDesktop *pCurrentDesktop;
    (void)m_pVirtualDesktopManagerInternal->GetCurrentDesktop(&pCurrentDesktop);

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

# include <assert.h>

#include "pref.cpp"

/* ------------------------------- MOCK FUNCTIONS START ------------------------------- */
// Mock all functions and classes which are external to the
// component under test, such as Windows API functions, library
// functions and functions defined in the other components.

LSTATUS
RegGetValueW(
    _In_ HKEY /* hkey */,
    _In_opt_ LPCWSTR /* lpSubKey */,
    _In_opt_ LPCWSTR /* lpValue */,
    _In_ DWORD /* dwFlags */,
    _Out_opt_ LPDWORD /* pdwType */,
    _When_((dwFlags & 0x7F) == RRF_RT_REG_SZ ||
               (dwFlags & 0x7F) == RRF_RT_REG_EXPAND_SZ ||
               (dwFlags & 0x7F) == (RRF_RT_REG_SZ | RRF_RT_REG_EXPAND_SZ) ||
               *pdwType == REG_SZ ||
               *pdwType == REG_EXPAND_SZ, _Post_z_)
        _When_((dwFlags & 0x7F) == RRF_RT_REG_MULTI_SZ ||
               *pdwType == REG_MULTI_SZ, _Post_ _NullNull_terminated_)
    _Out_writes_bytes_to_opt_(*pcbData,*pcbData) PVOID /* pvData */,
    _Inout_opt_ LPDWORD /* pcbData */
    )
{
    return ERROR_SUCCESS;
}

LSTATUS
RegOpenKeyExW(
    _In_ HKEY /* hKey */,
    _In_opt_ LPCWSTR /* lpSubKey */,
    _In_opt_ DWORD /* ulOptions */,
    _In_ REGSAM /* samDesired */,
    _Out_ PHKEY /* phkResult */
    )
{
    return ERROR_SUCCESS;
}

LSTATUS
RegSetValueExW(
    _In_ HKEY /* hKey */,
    _In_opt_ LPCWSTR /* lpValueName */,
    _Reserved_ DWORD /* Reserved */,
    _In_ DWORD /* dwType */,
    _In_reads_bytes_opt_(cbData) CONST BYTE* /* lpData */,
    _In_ DWORD /* cbData */
    )
{
    return ERROR_SUCCESS;
}

LSTATUS
RegCloseKey(
    _In_ HKEY /* hKey */
    )
{
    return ERROR_SUCCESS;
}

/* ------------------------------- MOCK FUNCTIONS END ------------------------------- */

/* ------------------------------- UNIT TESTS START ------------------------------- */

void InverseTest(void)
{
    assert(MF_CHECKED == Inverse(MF_UNCHECKED) && "Inverse of MF_UNCHECKED is wrong.");
    assert(MF_UNCHECKED == Inverse(MF_CHECKED) && "Inverse of MF_CHECKED is wrong.");
}

/* ------------------------------- UNIT TESTS END ------------------------------- */

int main(void)
{
    InverseTest();
    return 0;
}

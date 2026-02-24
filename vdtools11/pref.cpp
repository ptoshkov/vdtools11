#include <windows.h>

#include "pref.h"
#include "prop.h"

DWORD RegGetValueConvenience(const WCHAR flag[], const WCHAR errmsg[])
{
    DWORD value = MF_UNCHECKED;
    DWORD valuesize = sizeof(value);

    if (ERROR_SUCCESS != RegGetValue(HKEY_CURRENT_USER,
                                     SUBKEY,
                                     flag,
                                     RRF_RT_REG_DWORD,
                                     NULL,
                                     &value,
                                     &valuesize))
    {
        MessageBox(NULL, errmsg, TEXT("Error"), MB_OK);
    }

    return value;
}

DWORD prefStartOnHomeChecked(void)
{
    return RegGetValueConvenience(STARTONHOMEFLAG, TEXT("Failed to get registry value " STARTONHOMEFLAG "."));
}

DWORD prefJumpingChecked(void)
{
    return RegGetValueConvenience(JUMPINGFLAG, TEXT("Failed to get registry value " JUMPINGFLAG "."));
}

DWORD prefDraggingChecked(void)
{
    return RegGetValueConvenience(DRAGGINGFLAG, TEXT("Failed to get registry value " DRAGGINGFLAG "."));
}

DWORD Inverse(DWORD value)
{
    if (value)
    {
        return MF_UNCHECKED;
    }

    return MF_CHECKED;
}

void RegSetValueExConvenience(const WCHAR flag[], DWORD value, const WCHAR errmsg[])
{
    HKEY hKey;

    if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER, SUBKEY, 0, KEY_WRITE, &hKey))
    {
        MessageBox(NULL, TEXT("Failed to open registry key " SUBKEY "."), TEXT("Error"), MB_OK);
        return;
    }

    if (ERROR_SUCCESS != RegSetValueEx(hKey,
                                       flag,
                                       0,
                                       REG_DWORD,
                                       (const BYTE *)(&value),
                                       sizeof(value)))
    {
        MessageBox(NULL, errmsg, TEXT("Error"), MB_OK);
    }

    (void)RegCloseKey(hKey);
}

void prefToggleStartOnHome(void)
{
    DWORD value = Inverse(prefStartOnHomeChecked());
    RegSetValueExConvenience(STARTONHOMEFLAG, value, TEXT("Failed to set registry value " STARTONHOMEFLAG "."));
}

void prefToggleJumping(void)
{
    DWORD value = Inverse(prefJumpingChecked());
    RegSetValueExConvenience(JUMPINGFLAG, value, TEXT("Failed to set registry value " JUMPINGFLAG "."));
}

void prefToggleDragging(void)
{
    DWORD value = Inverse(prefDraggingChecked());
    RegSetValueExConvenience(DRAGGINGFLAG, value, TEXT("Failed to set registry value " DRAGGINGFLAG "."));
}

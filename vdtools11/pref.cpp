#include <windows.h>

#include "pref.h"
#include "prop.h"

#define STARTONHOMEFLAG_GET_FAILMSG TEXT("Failed to get registry value " STARTONHOMEFLAG ".")
#define JUMPINGFLAG_GET_FAILMSG TEXT("Failed to get registry value " JUMPINGFLAG ".")
#define DRAGGINGFLAG_GET_FAILMSG TEXT("Failed to get registry value " DRAGGINGFLAG ".")
#define STARTONHOMEFLAG_SET_FAILMSG TEXT("Failed to set registry value " STARTONHOMEFLAG ".")
#define JUMPINGFLAG_SET_FAILMSG TEXT("Failed to set registry value " JUMPINGFLAG ".")
#define DRAGGINGFLAG_SET_FAILMSG TEXT("Failed to set registry value " DRAGGINGFLAG ".")
#define SUBKEY_OPEN_FAILMSG TEXT("Failed to open registry key " SUBKEY ".")

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
    return RegGetValueConvenience(STARTONHOMEFLAG, STARTONHOMEFLAG_GET_FAILMSG);
}

DWORD prefJumpingChecked(void)
{
    return RegGetValueConvenience(JUMPINGFLAG, JUMPINGFLAG_GET_FAILMSG);
}

DWORD prefDraggingChecked(void)
{
    return RegGetValueConvenience(DRAGGINGFLAG, DRAGGINGFLAG_GET_FAILMSG);
}

void prefToggleStartOnHome(void)
{
    DWORD value = MF_CHECKED;

    if (prefStartOnHomeChecked())
    {
        value = MF_UNCHECKED;
    }

    HKEY hKey;

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, SUBKEY, 0, KEY_WRITE, &hKey))
    {
        LSTATUS result =
            RegSetValueEx(hKey, STARTONHOMEFLAG, 0, REG_DWORD, (const BYTE *)(&value), sizeof(value));

        if (ERROR_SUCCESS != result)
        {
            MessageBox(NULL, STARTONHOMEFLAG_SET_FAILMSG, TEXT("Error"), MB_OK);
        }

        (void)RegCloseKey(hKey);
    }
    else
    {
        MessageBox(NULL, SUBKEY_OPEN_FAILMSG, TEXT("Error"), MB_OK);
    }
}

void prefToggleJumping(void)
{
    DWORD value = MF_CHECKED;

    if (prefJumpingChecked())
    {
        value = MF_UNCHECKED;
    }

    HKEY hKey;

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, SUBKEY, 0, KEY_WRITE, &hKey))
    {
        LSTATUS result =
            RegSetValueEx(hKey, JUMPINGFLAG, 0, REG_DWORD, (const BYTE *)(&value), sizeof(value));

        if (ERROR_SUCCESS != result)
        {
            MessageBox(NULL, JUMPINGFLAG_SET_FAILMSG, TEXT("Error"), MB_OK);
        }

        (void)RegCloseKey(hKey);
    }
    else
    {
        MessageBox(NULL, SUBKEY_OPEN_FAILMSG, TEXT("Error"), MB_OK);
    }
}

void prefToggleDragging(void)
{
    DWORD value = MF_CHECKED;

    if (prefDraggingChecked())
    {
        value = MF_UNCHECKED;
    }

    HKEY hKey;

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, SUBKEY, 0, KEY_WRITE, &hKey))
    {
        LSTATUS result =
            RegSetValueEx(hKey, DRAGGINGFLAG, 0, REG_DWORD, (const BYTE *)(&value), sizeof(value));

        if (ERROR_SUCCESS != result)
        {
            MessageBox(NULL, DRAGGINGFLAG_SET_FAILMSG, TEXT("Error"), MB_OK);
        }

        (void)RegCloseKey(hKey);
    }
    else
    {
        MessageBox(NULL, SUBKEY_OPEN_FAILMSG, TEXT("Error"), MB_OK);
    }
}

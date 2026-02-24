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
        MessageBox(NULL, SUBKEY_OPEN_FAILMSG, TEXT("Error"), MB_OK);
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
    RegSetValueExConvenience(STARTONHOMEFLAG, value, STARTONHOMEFLAG_SET_FAILMSG);
}

void prefToggleJumping(void)
{
    DWORD value = Inverse(prefJumpingChecked());
    RegSetValueExConvenience(JUMPINGFLAG, value, JUMPINGFLAG_SET_FAILMSG);
}

void prefToggleDragging(void)
{
    DWORD value = Inverse(prefDraggingChecked());
    RegSetValueExConvenience(DRAGGINGFLAG, value, DRAGGINGFLAG_SET_FAILMSG);
}

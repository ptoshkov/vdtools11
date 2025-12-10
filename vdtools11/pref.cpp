#include <windows.h>

#include "pref.h"

#define APPNAME TEXT("VD Tools 11")
#define SUBKEY TEXT("Software\\" APPNAME)
#define STARTONHOMEFLAG TEXT("StartOnHomeFlag")
#define JUMPINGFLAG TEXT("JumpingFlag")
#define DRAGGINGFLAG TEXT("DraggingFlag")

DWORD prefStartOnHomeChecked(void)
{
    DWORD value = MF_UNCHECKED;
    DWORD valuesize = sizeof(value);

    if (ERROR_SUCCESS != RegGetValue(HKEY_CURRENT_USER,
                                     SUBKEY,
                                     STARTONHOMEFLAG,
                                     RRF_RT_REG_DWORD,
                                     NULL,
                                     &value,
                                     &valuesize))
    {
        MessageBox(NULL, TEXT("Failed to obtain registry value StartOnHomeFlag."), TEXT("Error"), MB_OK);
    }

    return value;
}

DWORD prefJumpingChecked(void)
{
    DWORD value = MF_UNCHECKED;
    DWORD valuesize = sizeof(value);

    if (ERROR_SUCCESS != RegGetValue(HKEY_CURRENT_USER,
                                     SUBKEY,
                                     JUMPINGFLAG,
                                     RRF_RT_REG_DWORD,
                                     NULL,
                                     &value,
                                     &valuesize))
    {
        MessageBox(NULL, TEXT("Failed to obtain registry value JumpingFlag."), TEXT("Error"), MB_OK);
    }

    return value;
}

DWORD prefDraggingChecked(void)
{
    DWORD value = MF_UNCHECKED;
    DWORD valuesize = sizeof(value);

    if (ERROR_SUCCESS != RegGetValue(HKEY_CURRENT_USER,
                                     SUBKEY,
                                     DRAGGINGFLAG,
                                     RRF_RT_REG_DWORD,
                                     NULL,
                                     &value,
                                     &valuesize))
    {
        MessageBox(NULL, TEXT("Failed to obtain registry value DraggingFlag."), TEXT("Error"), MB_OK);
    }

    return value;
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
        RegSetValueEx(hKey, STARTONHOMEFLAG, 0, REG_DWORD, (const BYTE *)(&value), sizeof(value));
        RegCloseKey(hKey);
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
        RegSetValueEx(hKey, JUMPINGFLAG, 0, REG_DWORD, (const BYTE *)(&value), sizeof(value));
        RegCloseKey(hKey);
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
        RegSetValueEx(hKey, DRAGGINGFLAG, 0, REG_DWORD, (const BYTE *)(&value), sizeof(value));
        RegCloseKey(hKey);
    }
}

#pragma once

#include <windows.h>

extern void (*uiJumpToDesktop)(UINT, BOOL);
extern UINT (*uiGetCurrentDesktop)(void);
extern DWORD (*uiStartOnHomeChecked)(void);
extern DWORD (*uiJumpingChecked)(void);
extern DWORD (*uiDraggingChecked)(void);
extern void (*uiToggleStartOnHome)(void);
extern void (*uiToggleJumping)(void);
extern void (*uiToggleDragging)(void);
void uiCreateWindow(HINSTANCE hInstance, const WCHAR szClassName[], const WCHAR szWindowName[]);
void uiAddTrayIcon(void);
void uiRegisterJumpKeys(void);
void uiRegisterDragKeys(void);
void uiStartMessageLoop(void);

#pragma once

#include <windows.h>

void coCreateInstances(void);
void coReleaseInstances(void);
void coJumpToDesktop(UINT idx, BOOL bMoveForegroundView);
UINT coGetCurrentDesktop(void);

#pragma once

#include <windows.h>

void logStart(void);
void logStop(void);
void logTrace(const WCHAR wmsg[]);
void logDebug(const WCHAR wmsg[]);
void logInfo(const WCHAR wmsg[]);
void logWarn(const WCHAR wmsg[]);
void logError(const WCHAR wmsg[]);
void logFatal(const WCHAR wmsg[]);

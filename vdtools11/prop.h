#pragma once

#include <windows.h>

#define ARG_TO_STR(ARG) #ARG
#define MACRO_EXPANSION_TO_STR(MACRO) ARG_TO_STR(MACRO)

#ifndef _REPODIR
#error _REPODIR not defined
#endif

#ifndef _BUILDDIR
#error _BUILDDIR not defined
#endif

#ifndef _RESOURCESDIR
#error _RESOURCESDIR not defined
#endif

#ifndef _CLASSNAME
#error _CLASSNAME not defined
#endif

#ifndef _WINDOWNAME
#error _WINDOWNAME not defined
#endif

#ifndef _APPNAME
#error _APPNAME not defined
#endif

#ifndef _EXENAME
#error _EXENAME not defined
#endif

#ifndef _LOGNAME
#error _LOGNAME not defined
#endif

#ifndef _INSTNAME
#error _INSTNAME not defined
#endif

#ifndef _UINSTNAME
#error _UINSTNAME not defined
#endif

#ifndef _STARTONHOMEFLAG
#error _STARTONHOMEFLAG not defined
#endif

#ifndef _JUMPINGFLAG
#error _JUMPINGFLAG not defined
#endif

#ifndef _DRAGGINGFLAG
#error _DRAGGINGFLAG not defined
#endif

#define BUILDDIR TEXT(MACRO_EXPANSION_TO_STR(_BUILDDIR))
#define CLASSNAME TEXT(MACRO_EXPANSION_TO_STR(_CLASSNAME))
#define WINDOWNAME TEXT(MACRO_EXPANSION_TO_STR(_WINDOWNAME))
#define APPNAME TEXT(MACRO_EXPANSION_TO_STR(_APPNAME))
#define EXENAME TEXT(MACRO_EXPANSION_TO_STR(_EXENAME))
#define LOGNAME TEXT(MACRO_EXPANSION_TO_STR(_LOGNAME))
#define INSTNAME TEXT(MACRO_EXPANSION_TO_STR(_INSTNAME))
#define UINSTNAME TEXT(MACRO_EXPANSION_TO_STR(_UINSTNAME))
#define STARTONHOMEFLAG TEXT(MACRO_EXPANSION_TO_STR(_STARTONHOMEFLAG))
#define JUMPINGFLAG TEXT(MACRO_EXPANSION_TO_STR(_JUMPINGFLAG))
#define DRAGGINGFLAG TEXT(MACRO_EXPANSION_TO_STR(_DRAGGINGFLAG))
#define SUBKEY TEXT("Software\\" APPNAME)

// See copyright notice in scse_copyright.txt

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define UNUSED(x) ((void)(x)) // to avoid warnings

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <Windows.h>

// TODO: reference additional headers your program requires here
#include <stdio.h>
#include <time.h>

#include "..\scse_common\SCSE_Version.h"
#include "..\scse_common\Log.h"
#include "..\scse_lualinker\LuaLinker.h"
#include "..\scse_lualinker\lua.h"
#include "..\scse_lualinker\lauxlib.h"
#include "..\scse_lualinker\lualib.h"

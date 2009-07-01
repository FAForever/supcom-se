// See copyright notice in scse_copyright.txt

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// TODO: reference additional headers your program requires here

#include <Windows.h>
#include <Psapi.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "..\scse_common\Types.h"
#include "..\scse_common\Log.h"
#include "..\scse_common\Checksum.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

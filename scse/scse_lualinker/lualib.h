// See copyright notice in scse_copyright.txt

#pragma once

#include "lua.h"

#ifndef LUALIB_API
#define LUALIB_API	LUA_API
#endif

#define LUA_IOLIBNAME	"io"
#define LUA_OSLIBNAME	"os"
typedef int (*lualinkeropen_io) (lua_State *L);
LUALIB_API lualinkeropen_io luaopen_io;


/* to help testing the libraries */
#ifndef lua_assert
#define lua_assert(c)   /* empty */
#endif


/* compatibility code */
#define lua_iolibopen   luaopen_io

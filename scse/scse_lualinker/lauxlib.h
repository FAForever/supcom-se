// See copyright notice in scse_copyright.txt

#pragma once

#include "lua.h"


#ifndef LUALIB_API
#define LUALIB_API LUA_API
#endif


typedef struct luaL_reg {
  const char *name;
  lua_CFunction func;
} luaL_reg;


typedef void (*lualinkerL_openlib) (lua_State *L, const char *libname, 
                                    const luaL_reg *l, int nup);
typedef const char* (*lualinkerL_checklstring) (lua_State *L, int numArg, size_t *l);

LUALIB_API lualinkerL_openlib luaL_openlib;
LUALIB_API lualinkerL_checklstring luaL_checklstring;

/*
** ===============================================================
** some useful macros
** ===============================================================
*/
#define luaL_checkstring(L,n)	(luaL_checklstring(L, (n), NULL))

// See copyright notice in scse_copyright.txt

// scse.cpp : Defines the exported functions for the DLL application.

#include "stdafx.h"
#include "scse.h"

// Return version of SCSE.
//
// Return to lua values:
// 1. String value with version of SCSE.
static int scse_version (lua_State *L)
{
    lua_pushstring(L, SCSE_VERSION);
    return 1;
}

// Return the elapsed wall-clock time in seconds since the start of the process.
//
// Return to lua values:
// 1. Number value with the elapsed wall-clock time in seconds since the start of the process.
static int scse_clock (lua_State *L)
{
    lua_pushnumber(L, (lua_Number)clock() / (lua_Number)CLOCKS_PER_SEC);
    return 1;
}

static const luaL_reg scselib[] = {
    {"version", scse_version},
    {"clock", scse_clock},
    {NULL, NULL}
};

// Link lua linker functions with SupCom lua functions and open scse library.
//
// Return to lua values:
// 1. Table "scse" with functions.
SCSE_API int luaopen_scse(lua_State *L)
{
    // Link lua linker functions with Supreme Commander lua functions
    if(LuaLinker::Link())
    {
        log.LogMessage("Lua linker functions successefully linked with Supreme Commander lua functions.\n");
        // Open scse library
        luaL_openlib(L, SCSE_SCSELIBNAME, scselib, 0);
        log.LogMessage("SCSE library successefully opened.\n");
    }
    else
        log.LogMessage("ERROR: Couldn't link lua linker functions with Supreme Commander lua functions!\n");

    return 1;
}

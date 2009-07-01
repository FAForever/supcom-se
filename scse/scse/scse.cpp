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

static luaL_reg scselib[] = {
    {"version", scse_version},
    {"luaopen_io", NULL}, // address sets after linking
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

        // Set address of luaopen_io function in scselib array
        scselib[1].func = luaopen_io;

        // Open scse library
        luaL_openlib(L, SCSE_SCSELIBNAME, scselib, 0);

        log.LogMessage("SCSE library successefully opened.\n");
    }
    else
        log.LogMessage("ERROR: Couldn't link lua linker functions with Supreme Commander lua functions!\n");

    return 1;
}

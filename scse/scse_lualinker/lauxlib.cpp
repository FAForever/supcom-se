// See copyright notice in scse_copyright.txt

#include "StdAfx.h"
#include "lauxlib.h"

lualinkerL_openlib      luaL_openlib;
lualinkerL_getmetafield luaL_getmetafield;
lualinkerL_callmeta     luaL_callmeta;
lualinkerL_typerror     luaL_typerror;
lualinkerL_argerror     luaL_argerror;
lualinkerL_checklstring luaL_checklstring;
lualinkerL_optlstring   luaL_optlstring;
lualinkerL_checknumber  luaL_checknumber;
lualinkerL_optnumber    luaL_optnumber;

lualinkerL_checkstack   luaL_checkstack;
lualinkerL_checktype    luaL_checktype;
lualinkerL_checkany     luaL_checkany;

lualinkerL_newmetatable luaL_newmetatable;
lualinkerL_getmetatable luaL_getmetatable;
//lualinkerL_checkudata  luaL_checkudata;

lualinkerL_where    luaL_where;
lualinkerL_error    luaL_error;

lualinkerL_findstring   luaL_findstring;

lualinkerL_ref      luaL_ref;
lualinkerL_unref    luaL_unref;

lualinkerL_getn luaL_getn;
lualinkerL_setn luaL_setn;

lualinkerL_loadfile     luaL_loadfile;
lualinkerL_loadbuffer   luaL_loadbuffer;

/*
** Generic Buffer manipulation
*/
lualinkerL_buffinit     luaL_buffinit;
lualinkerL_prepbuffer   luaL_prepbuffer;
lualinkerL_addlstring   luaL_addlstring;
lualinkerL_addstring    luaL_addstring;
lualinkerL_addvalue     luaL_addvalue;
lualinkerL_pushresult   luaL_pushresult;

/*
** Compatibility functions
*/
lualinker_dofile    lua_dofile;
lualinker_dostring  lua_dostring;
lualinker_dobuffer  lua_dobuffer;

// See copyright notice in scse_copyright.txt

#include "StdAfx.h"
#include "lua.h"

/*
** access functions (stack -> C)
*/
lualinker_isnumber      lua_isnumber;
lualinker_isstring      lua_isstring;
//lualinker_iscfunction   lua_iscfunction; // SupCom haven't definition for this function
lualinker_isuserdata    lua_isuserdata;
lualinker_type          lua_type;
lualinker_typename      lua_typename;

lualinker_equal         lua_equal;
lualinker_rawequal      lua_rawequal;
lualinker_lessthan      lua_lessthan;

lualinker_tonumber      lua_tonumber;
lualinker_toboolean     lua_toboolean;
lualinker_tostring      lua_tostring;
lualinker_strlen        lua_strlen;
lualinker_tocfunction   lua_tocfunction;
lualinker_touserdata    lua_touserdata;
lualinker_tothread      lua_tothread;
lualinker_topointer     lua_topointer;


/*
** push functions (C -> stack)
*/
lualinker_pushnil           lua_pushnil;
lualinker_pushnumber        lua_pushnumber;
lualinker_pushlstring       lua_pushlstring;
lualinker_pushstring        lua_pushstring;
lualinker_pushvfstring      lua_pushvfstring;
lualinker_pushfstring       lua_pushfstring;
lualinker_pushcclosure      lua_pushcclosure;
lualinker_pushboolean       lua_pushboolean;
lualinker_pushlightuserdata lua_pushlightuserdata;


/*
** get functions (Lua -> stack)
*/
lualinker_gettable  lua_gettable;


/*
** `load' and `call' functions (load and run Lua code)
*/
lualinker_call  lua_call;

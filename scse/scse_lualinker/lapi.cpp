// See copyright notice in scse_copyright.txt

#include "StdAfx.h"
#include "lua.h"

//lualinker_atpanic lua_atpanic; // SupCom haven't definition for this function
lualinker_newthread lua_newthread;

/*
** basic stack manipulation
*/
lualinker_gettop        lua_gettop;
lualinker_settop        lua_settop;
lualinker_pushvalue     lua_pushvalue;
lualinker_remove        lua_remove;
lualinker_insert        lua_insert;
lualinker_replace       lua_replace;
lualinker_checkstack    lua_checkstack;

lualinker_xmove         lua_xmove;

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
//lualinker_touserdata    lua_touserdata; // SupCom haven't definition for this function (actually SupCom have lua_touserdata with different syntax)
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
lualinker_gettable      lua_gettable;
lualinker_rawget        lua_rawget;
lualinker_rawgeti       lua_rawgeti;
lualinker_newtable      lua_newtable;
//lualinker_newuserdata   lua_newuserdata; // SupCom haven't definition for this function (actually SupCom have lua_newuserdata with different syntax)
lualinker_getmetatable  lua_getmetatable;
lualinker_getfenv       lua_getfenv;


/*
** set functions (stack -> Lua)
*/
lualinker_settable      lua_settable;
lualinker_rawset        lua_rawset;
lualinker_rawseti       lua_rawseti;
lualinker_setmetatable  lua_setmetatable;
lualinker_setfenv       lua_setfenv;


/*
** `load' and `call' functions (load and run Lua code)
*/
lualinker_call      lua_call;
lualinker_pcall     lua_pcall;
lualinker_cpcall    lua_cpcall;
lualinker_load      lua_load;
lualinker_dump      lua_dump;


/*
** garbage-collection functions
*/
lualinker_getgcthreshold    lua_getgcthreshold;
lualinker_getgccount        lua_getgccount;
lualinker_setgcthreshold    lua_setgcthreshold;


/*
** miscellaneous functions
*/
lualinker_version   lua_version;
lualinker_error     lua_error;
lualinker_next      lua_next;
lualinker_concat    lua_concat;

/*
** compatibility functions
*/
lualinker_pushupvalues lua_pushupvalues;

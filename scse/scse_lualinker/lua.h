// See copyright notice in scse_copyright.txt

#pragma once

#define LUA_VERSION     "Lua 5.0.1"
#define LUA_COPYRIGHT   "Copyright (C) 1994-2003 Tecgraf, PUC-Rio"
#define LUA_AUTHORS     "R. Ierusalimschy, L. H. de Figueiredo & W. Celes"


/* option for multiple returns in `lua_pcall' and `lua_call' */
#define LUA_MULTRET (-1)


/*
** pseudo-indices
*/
#define LUA_REGISTRYINDEX   (-10000)
#define LUA_GLOBALSINDEX    (-10001)
#define lua_upvalueindex(i) (LUA_GLOBALSINDEX-(i))


/* error codes for `lua_load' and `lua_pcall' */
#define LUA_ERRRUN      1
#define LUA_ERRFILE     2
#define LUA_ERRSYNTAX	3
#define LUA_ERRMEM      4
#define LUA_ERRERR      5

typedef void lua_State;

typedef int (*lua_CFunction) (lua_State *L);


/*
** functions that read/write blocks when loading/dumping Lua chunks
*/
typedef const char * (*lua_Chunkreader) (lua_State *L, void *ud, size_t *sz);

typedef int (*lua_Chunkwriter) (lua_State *L, const void* p,
                                size_t sz, void* ud);


/* type of numbers in Lua */
#ifndef LUA_NUMBER
typedef float lua_Number; // Supreme Commander use float instead of double
#else
typedef LUA_NUMBER lua_Number;
#endif


/* mark for all lua API functions */
#ifndef LUA_API
#define LUA_API extern
#endif


/* mark for all lua linker API functions */
#ifndef LUALINKER_API
#define LUALINKER_API LUA_API
#endif

/*
** access functions (stack -> C)
*/
typedef int             (*lualinker_isnumber) (lua_State *L, int idx);
typedef int             (*lualinker_isstring) (lua_State *L, int idx);
typedef int             (*lualinker_iscfunction) (lua_State *L, int idx);
typedef int             (*lualinker_isuserdata) (lua_State *L, int idx);
typedef int             (*lualinker_type) (lua_State *L, int idx);
typedef const char*     (*lualinker_typename) (lua_State *L, int tp);

typedef int             (*lualinker_equal) (lua_State *L, int idx1, int idx2);
typedef int             (*lualinker_rawequal) (lua_State *L, int idx1, int idx2);
typedef int             (*lualinker_lessthan) (lua_State *L, int idx1, int idx2);

typedef lua_Number      (*lualinker_tonumber) (lua_State *L, int idx);
typedef int             (*lualinker_toboolean) (lua_State *L, int idx);
typedef const char*     (*lualinker_tostring) (lua_State *L, int idx);
typedef size_t          (*lualinker_strlen) (lua_State *L, int idx);
typedef lua_CFunction   (*lualinker_tocfunction) (lua_State *L, int idx);
typedef void*	        (*lualinker_touserdata) (lua_State *L, int idx);
typedef lua_State*      (*lualinker_tothread) (lua_State *L, int idx);
typedef const void*     (*lualinker_topointer) (lua_State *L, int idx);

LUA_API lualinker_isnumber      lua_isnumber;
LUA_API lualinker_isstring      lua_isstring;
//LUA_API lualinker_iscfunction   lua_iscfunction; // SupCom haven't definition for this function
LUA_API lualinker_isuserdata    lua_isuserdata;
LUA_API lualinker_type          lua_type;
LUA_API lualinker_typename      lua_typename;

LUA_API lualinker_equal         lua_equal;
LUA_API lualinker_rawequal      lua_rawequal;
LUA_API lualinker_lessthan      lua_lessthan;

LUA_API lualinker_tonumber      lua_tonumber;
LUA_API lualinker_toboolean     lua_toboolean;
LUA_API lualinker_tostring      lua_tostring;
LUA_API lualinker_strlen        lua_strlen;
LUA_API lualinker_tocfunction   lua_tocfunction;
LUA_API lualinker_touserdata    lua_touserdata;
LUA_API lualinker_tothread      lua_tothread;
LUA_API lualinker_topointer     lua_topointer;


/*
** push functions (C -> stack)
*/
typedef void        (*lualinker_pushnil) (lua_State *L);
typedef void        (*lualinker_pushnumber) (lua_State *L, lua_Number n);
typedef void        (*lualinker_pushlstring) (lua_State *L, const char *s, size_t l);
typedef void        (*lualinker_pushstring) (lua_State *L, const char *s);
typedef const char* (*lualinker_pushvfstring) (lua_State *L, const char *fmt, va_list argp);
typedef const char* (*lualinker_pushfstring) (lua_State *L, const char *fmt, ...);
typedef void        (*lualinker_pushcclosure) (lua_State *L, lua_CFunction fn, int n);
typedef void        (*lualinker_pushboolean) (lua_State *L, int b);
typedef void        (*lualinker_pushlightuserdata) (lua_State *L, void *p);

LUA_API lualinker_pushnil           lua_pushnil;
LUA_API lualinker_pushnumber        lua_pushnumber;
LUA_API lualinker_pushlstring       lua_pushlstring;
LUA_API lualinker_pushstring        lua_pushstring;
LUA_API lualinker_pushvfstring      lua_pushvfstring;
LUA_API lualinker_pushfstring       lua_pushfstring;
LUA_API lualinker_pushcclosure      lua_pushcclosure;
LUA_API lualinker_pushboolean       lua_pushboolean;
LUA_API lualinker_pushlightuserdata lua_pushlightuserdata;


/*
** get functions (Lua -> stack)
*/
typedef void    (*lualinker_gettable) (lua_State *L, int idx);

LUA_API lualinker_gettable  lua_gettable;


/*
** `load' and `call' functions (load and run Lua code)
*/
typedef void    (*lualinker_call) (lua_State *L, int nargs, int nresults);

LUA_API lualinker_call  lua_call;


/* 
** ===============================================================
** some useful macros
** ===============================================================
*/


/*
** compatibility macros and functions
*/
#define lua_getglobal(L,s)	\
		(lua_pushstring(L, s), lua_gettable(L, LUA_GLOBALSINDEX))

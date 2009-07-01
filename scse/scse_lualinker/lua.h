// See copyright notice in scse_copyright.txt

#pragma once

#define LUA_VERSION     "Lua 5.0.1"
#define LUA_COPYRIGHT   "Copyright (C) 1994-2003 Tecgraf, PUC-Rio"
#define LUA_AUTHORS     "R. Ierusalimschy, L. H. de Figueiredo & W. Celes"


/* option for multiple returns in `lua_pcall' and `lua_call' */
#define LUA_MULTRET (-1) // not tested


/*
** pseudo-indices
*/
#define LUA_REGISTRYINDEX   (-10000) // not tested
#define LUA_GLOBALSINDEX    (-10001)
#define lua_upvalueindex(i) (LUA_GLOBALSINDEX-(i)) // not tested


/* error codes for `lua_load' and `lua_pcall' */
#define LUA_ERRRUN      1 // not tested
#define LUA_ERRFILE     2 // not tested
#define LUA_ERRSYNTAX	3 // not tested
#define LUA_ERRMEM      4 // not tested
#define LUA_ERRERR      5 // not tested

typedef void lua_State;

typedef int (*lua_CFunction) (lua_State *L);


/*
** functions that read/write blocks when loading/dumping Lua chunks
*/
typedef const char * (*lua_Chunkreader) (lua_State *L, void *ud, size_t *sz);

typedef int (*lua_Chunkwriter) (lua_State *L, const void* p,
                                size_t sz, void* ud);


/*
** basic types
*/
#define LUA_TNONE           (-1) // not tested
#define LUA_TNIL            0 // not tested
#define LUA_TBOOLEAN        1 // not tested
#define LUA_TLIGHTUSERDATA  2 // not tested
#define LUA_TNUMBER         3 // not tested
#define LUA_TSTRING         4 // not tested
#define LUA_TTABLE          5 // not tested
#define LUA_TFUNCTION       6 // not tested
#define LUA_TUSERDATA       7 // not tested
#define LUA_TTHREAD         8 // not tested


/* minimum Lua stack available to a C function */
#define LUA_MINSTACK    20 // not tested


/*
** generic extra include file
*/
#ifdef LUA_USER_H
#include LUA_USER_H
#endif


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
** state manipulation
*/
typedef lua_State*  (*lualinker_open) (void);
typedef void        (*lualinker_close) (lua_State *L);
typedef lua_State*  (*lualinker_newthread) (lua_State *L);

typedef lua_CFunction (*lualinker_atpanic) (lua_State *L, lua_CFunction panicf);

LUA_API lualinker_open      lua_open;
LUA_API lualinker_close     lua_close;
LUA_API lualinker_newthread lua_newthread;

//LUA_API lualinker_atpanic lua_atpanic; // SupCom haven't definition for this function


/*
** basic stack manipulation
*/
typedef int     (*lualinker_gettop) (lua_State *L);
typedef void    (*lualinker_settop) (lua_State *L, int idx);
typedef void    (*lualinker_pushvalue) (lua_State *L, int idx);
typedef void    (*lualinker_remove) (lua_State *L, int idx);
typedef void    (*lualinker_insert) (lua_State *L, int idx);
typedef void    (*lualinker_replace) (lua_State *L, int idx);
typedef int     (*lualinker_checkstack) (lua_State *L, int sz);

typedef void    (*lualinker_xmove) (lua_State *from, lua_State *to, int n);

LUA_API lualinker_gettop        lua_gettop;
LUA_API lualinker_settop        lua_settop;
LUA_API lualinker_pushvalue     lua_pushvalue;
LUA_API lualinker_remove        lua_remove;
LUA_API lualinker_insert        lua_insert;
LUA_API lualinker_replace       lua_replace;
LUA_API lualinker_checkstack    lua_checkstack;

LUA_API lualinker_xmove         lua_xmove;


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
//LUA_API lualinker_touserdata    lua_touserdata; // SupCom haven't definition for this function (actually SupCom have lua_touserdata with different syntax)
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
typedef void    (*lualinker_rawget) (lua_State *L, int idx);
typedef void    (*lualinker_rawgeti) (lua_State *L, int idx, int n);
typedef void    (*lualinker_newtable) (lua_State *L);
typedef void*   (*lualinker_newuserdata) (lua_State *L, size_t sz);
typedef int     (*lualinker_getmetatable) (lua_State *L, int objindex);
typedef void    (*lualinker_getfenv) (lua_State *L, int idx);

LUA_API lualinker_gettable      lua_gettable;
LUA_API lualinker_rawget        lua_rawget;
LUA_API lualinker_rawgeti       lua_rawgeti;
LUA_API lualinker_newtable      lua_newtable;
//LUA_API lualinker_newuserdata   lua_newuserdata; // SupCom haven't definition for this function (actually SupCom have lua_newuserdata with different syntax)
LUA_API lualinker_getmetatable  lua_getmetatable;
LUA_API lualinker_getfenv       lua_getfenv;


/*
** set functions (stack -> Lua)
*/
typedef void    (*lualinker_settable) (lua_State *L, int idx);
typedef void    (*lualinker_rawset) (lua_State *L, int idx);
typedef void    (*lualinker_rawseti) (lua_State *L, int idx, int n);
typedef int     (*lualinker_setmetatable) (lua_State *L, int objindex);
typedef int     (*lualinker_setfenv) (lua_State *L, int idx);

LUA_API lualinker_settable      lua_settable;
LUA_API lualinker_rawset        lua_rawset;
LUA_API lualinker_rawseti       lua_rawseti;
LUA_API lualinker_setmetatable  lua_setmetatable;
LUA_API lualinker_setfenv       lua_setfenv;


/*
** `load' and `call' functions (load and run Lua code)
*/
typedef void    (*lualinker_call) (lua_State *L, int nargs, int nresults);
typedef int     (*lualinker_pcall) (lua_State *L, int nargs, int nresults, int errfunc);
typedef int     (*lualinker_cpcall) (lua_State *L, lua_CFunction func, void *ud);
typedef int     (*lualinker_load) (lua_State *L, lua_Chunkreader reader, void *dt, const char *chunkname);
typedef int     (*lualinker_dump) (lua_State *L, lua_Chunkwriter writer, void *data);

LUA_API lualinker_call      lua_call;
LUA_API lualinker_pcall     lua_pcall;
LUA_API lualinker_cpcall    lua_cpcall;
LUA_API lualinker_load      lua_load;
LUA_API lualinker_dump      lua_dump;


/*
** coroutine functions
*/
typedef int (*lualinker_yield) (lua_State *L, int nresults);
typedef int (*lualinker_resume) (lua_State *L, int narg);

LUA_API lualinker_yield     lua_yield;
LUA_API lualinker_resume    lua_resume;


/*
** garbage-collection functions
*/
typedef int     (*lualinker_getgcthreshold) (lua_State *L);
typedef int     (*lualinker_getgccount) (lua_State *L);
typedef void    (*lualinker_setgcthreshold) (lua_State *L, int newthreshold);

LUA_API lualinker_getgcthreshold    lua_getgcthreshold;
LUA_API lualinker_getgccount        lua_getgccount;
LUA_API lualinker_setgcthreshold    lua_setgcthreshold;


/*
** miscellaneous functions
*/
typedef const char* (*lualinker_version) (void);
typedef int         (*lualinker_error) (lua_State *L);
typedef int         (*lualinker_next) (lua_State *L, int idx);
typedef void        (*lualinker_concat) (lua_State *L, int n);

LUA_API lualinker_version   lua_version;
LUA_API lualinker_error     lua_error;
LUA_API lualinker_next      lua_next;
LUA_API lualinker_concat    lua_concat;


/* 
** ===============================================================
** some useful macros
** ===============================================================
*/

//#define lua_boxpointer(L,u) \
//    (*(void **)(lua_newuserdata(L, sizeof(void *))) = (u))
//
//#define lua_unboxpointer(L,i)	(*(void **)(lua_touserdata(L, i)))

#define lua_pop(L,n)		lua_settop(L, -(n)-1)

#define lua_register(L,n,f) \
    (lua_pushstring(L, n), \
     lua_pushcfunction(L, f), \
     lua_settable(L, LUA_GLOBALSINDEX))

#define lua_pushcfunction(L,f)	lua_pushcclosure(L, f, 0)

#define lua_isfunction(L,n)         (lua_type(L,n) == LUA_TFUNCTION)
#define lua_istable(L,n)            (lua_type(L,n) == LUA_TTABLE)
#define lua_islightuserdata(L,n)    (lua_type(L,n) == LUA_TLIGHTUSERDATA)
#define lua_isnil(L,n)              (lua_type(L,n) == LUA_TNIL)
#define lua_isboolean(L,n)          (lua_type(L,n) == LUA_TBOOLEAN)
#define lua_isnone(L,n)             (lua_type(L,n) == LUA_TNONE)
#define lua_isnoneornil(L, n)       (lua_type(L,n) <= 0)

#define lua_pushliteral(L, s)	\
    lua_pushlstring(L, "" s, (sizeof(s)/sizeof(char))-1)


/*
** compatibility macros and functions
*/
typedef int (*lualinker_pushupvalues) (lua_State *L);

LUA_API lualinker_pushupvalues lua_pushupvalues;

#define lua_getregistry(L)	lua_pushvalue(L, LUA_REGISTRYINDEX)
#define lua_setglobal(L,s)	\
    (lua_pushstring(L, s), lua_insert(L, -2), lua_settable(L, LUA_GLOBALSINDEX))
#define lua_getglobal(L,s)	\
    (lua_pushstring(L, s), lua_gettable(L, LUA_GLOBALSINDEX))

/* compatibility with ref system */

/* pre-defined references */
#define LUA_NOREF	(-2) // not tested
#define LUA_REFNIL	(-1) // not tested

#define lua_ref(L,lock)	((lock) ? luaL_ref(L, LUA_REGISTRYINDEX) : \
      (lua_pushstring(L, "unlocked references are obsolete"), lua_error(L), 0))
#define lua_unref(L,ref)	luaL_unref(L, LUA_REGISTRYINDEX, (ref))
#define lua_getref(L,ref)	lua_rawgeti(L, LUA_REGISTRYINDEX, ref)


/*
** {======================================================================
** useful definitions for Lua kernel and libraries
** =======================================================================
*/

/* formats for Lua numbers */
#ifndef LUA_NUMBER_SCAN
#define LUA_NUMBER_SCAN		"%lf"
#endif

#ifndef LUA_NUMBER_FMT
#define LUA_NUMBER_FMT		"%.14g"
#endif

/* }====================================================================== */


/*
** {======================================================================
** Debug API
** =======================================================================
*/


/*
** Event codes
*/
#define LUA_HOOKCALL    0 // not tested
#define LUA_HOOKRET     1 // not tested
#define LUA_HOOKLINE    2 // not tested
#define LUA_HOOKCOUNT   3 // not tested
#define LUA_HOOKTAILRET 4 // not tested


/*
** Event masks
*/
#define LUA_MASKCALL    (1 << LUA_HOOKCALL) // not tested
#define LUA_MASKRET     (1 << LUA_HOOKRET) // not tested
#define LUA_MASKLINE    (1 << LUA_HOOKLINE) // not tested
#define LUA_MASKCOUNT   (1 << LUA_HOOKCOUNT) // not tested

typedef struct lua_Debug lua_Debug;  /* activation record */ // not tested

typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);


typedef int         (*lualinker_getstack) (lua_State *L, int level, lua_Debug *ar); // not tested
typedef int         (*lualinker_getinfo) (lua_State *L, const char *what, lua_Debug *ar); // not tested
typedef const char* (*lualinker_getlocal) (lua_State *L, const lua_Debug *ar, int n); // not tested
typedef const char* (*lualinker_setlocal) (lua_State *L, const lua_Debug *ar, int n); // not tested
typedef const char* (*lualinker_getupvalue) (lua_State *L, int funcindex, int n);
typedef const char* (*lualinker_setupvalue) (lua_State *L, int funcindex, int n);

typedef int         (*lualinker_sethook) (lua_State *L, lua_Hook func, int mask, int count);
typedef lua_Hook    (*lualinker_gethook) (lua_State *L);
typedef int         (*lualinker_gethookmask) (lua_State *L);
typedef int         (*lualinker_gethookcount) (lua_State *L);

LUA_API lualinker_getstack      lua_getstack;
LUA_API lualinker_getinfo       lua_getinfo;
LUA_API lualinker_getlocal      lua_getlocal;
LUA_API lualinker_setlocal      lua_setlocal;
LUA_API lualinker_getupvalue    lua_getupvalue;
LUA_API lualinker_setupvalue    lua_setupvalue;

LUA_API lualinker_sethook       lua_sethook;
LUA_API lualinker_gethook       lua_gethook;
LUA_API lualinker_gethookmask   lua_gethookmask;
LUA_API lualinker_gethookcount  lua_gethookcount;


#define LUA_IDSIZE	60 // not tested

struct lua_Debug { // not tested
  int event;
  const char *name;	/* (n) */
  const char *namewhat;	/* (n) `global', `local', `field', `method' */
  const char *what;	/* (S) `Lua', `C', `main', `tail' */
  const char *source;	/* (S) */
  int currentline;	/* (l) */
  int nups;		/* (u) number of upvalues */
  int linedefined;	/* (S) */
  char short_src[LUA_IDSIZE]; /* (S) */
  /* private part */
  int i_ci;  /* active function */
};

/* }====================================================================== */

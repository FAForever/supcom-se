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


typedef void        (*lualinkerL_openlib) (lua_State *L, const char *libname, 
                                           const luaL_reg *l, int nup);
typedef int         (*lualinkerL_getmetafield) (lua_State *L, int obj, const char *e);
typedef int         (*lualinkerL_callmeta) (lua_State *L, int obj, const char *e);
typedef int         (*lualinkerL_typerror) (lua_State *L, int narg, const char *tname);
typedef int         (*lualinkerL_argerror) (lua_State *L, int numarg, const char *extramsg);
typedef const char* (*lualinkerL_checklstring) (lua_State *L, int numArg, size_t *l);
typedef const char* (*lualinkerL_optlstring) (lua_State *L, int numArg,
                                              const char *def, size_t *l);
typedef lua_Number  (*lualinkerL_checknumber) (lua_State *L, int numArg);
typedef lua_Number  (*lualinkerL_optnumber) (lua_State *L, int nArg, lua_Number def);

typedef void    (*lualinkerL_checkstack) (lua_State *L, int sz, const char *msg);
typedef void    (*lualinkerL_checktype) (lua_State *L, int narg, int t);
typedef void    (*lualinkerL_checkany) (lua_State *L, int narg);

typedef int     (*lualinkerL_newmetatable) (lua_State *L, const char *tname);
typedef void    (*lualinkerL_getmetatable) (lua_State *L, const char *tname);
typedef void*   (*lualinkerL_checkudata) (lua_State *L, int ud, const char *tname);

typedef void    (*lualinkerL_where) (lua_State *L, int lvl);
typedef int     (*lualinkerL_error) (lua_State *L, const char *fmt, ...);

typedef int     (*lualinkerL_findstring) (const char *st, const char *const lst[]);

typedef int     (*lualinkerL_ref) (lua_State *L, int t);
typedef void    (*lualinkerL_unref) (lua_State *L, int t, int ref);

typedef int     (*lualinkerL_getn) (lua_State *L, int t);
typedef void    (*lualinkerL_setn) (lua_State *L, int t, int n);

typedef int     (*lualinkerL_loadfile) (lua_State *L, const char *filename);
typedef int     (*lualinkerL_loadbuffer) (lua_State *L, const char *buff, size_t sz,
                                          const char *name);

LUALIB_API lualinkerL_openlib luaL_openlib;
LUALIB_API lualinkerL_getmetafield luaL_getmetafield;
LUALIB_API lualinkerL_callmeta luaL_callmeta;
LUALIB_API lualinkerL_typerror luaL_typerror;
LUALIB_API lualinkerL_argerror luaL_argerror;
LUALIB_API lualinkerL_checklstring luaL_checklstring;
LUALIB_API lualinkerL_optlstring luaL_optlstring;
LUALIB_API lualinkerL_checknumber luaL_checknumber;
LUALIB_API lualinkerL_optnumber luaL_optnumber;

LUALIB_API lualinkerL_checkstack luaL_checkstack;
LUALIB_API lualinkerL_checktype luaL_checktype;
LUALIB_API lualinkerL_checkany luaL_checkany;

LUALIB_API lualinkerL_newmetatable   luaL_newmetatable;
LUALIB_API lualinkerL_getmetatable  luaL_getmetatable;
//LUALIB_API lualinkerL_checkudata luaL_checkudata;

LUALIB_API lualinkerL_where luaL_where;
LUALIB_API lualinkerL_error luaL_error;

LUALIB_API lualinkerL_findstring luaL_findstring;

LUALIB_API lualinkerL_ref luaL_ref;
LUALIB_API lualinkerL_unref luaL_unref;

LUALIB_API lualinkerL_getn luaL_getn;
LUALIB_API lualinkerL_setn luaL_setn;

LUALIB_API lualinkerL_loadfile luaL_loadfile;
LUALIB_API lualinkerL_loadbuffer luaL_loadbuffer;


/*
** ===============================================================
** some useful macros
** ===============================================================
*/
#define luaL_argcheck(L, cond,numarg,extramsg) if (!(cond)) \
                                                   luaL_argerror(L, numarg,extramsg)
#define luaL_checkstring(L,n)	(luaL_checklstring(L, (n), NULL))
#define luaL_optstring(L,n,d)	(luaL_optlstring(L, (n), (d), NULL))
#define luaL_checkint(L,n)	((int)luaL_checknumber(L, n))
#define luaL_checklong(L,n)	((long)luaL_checknumber(L, n))
#define luaL_optint(L,n,d)	((int)luaL_optnumber(L, n,(lua_Number)(d)))
#define luaL_optlong(L,n,d)	((long)luaL_optnumber(L, n,(lua_Number)(d)))


/*
** {======================================================
** Generic Buffer manipulation
** =======================================================
*/

#ifndef LUAL_BUFFERSIZE
#define LUAL_BUFFERSIZE	  BUFSIZ // where defined BUFSIZ??? o.O
#endif


typedef struct luaL_Buffer { // not tested
    char *p;			/* current position in buffer */
    int lvl;  /* number of strings in the stack (level) */
    lua_State *L;
    char buffer[LUAL_BUFFERSIZE];
} luaL_Buffer;

#define luaL_putchar(B,c) \
    ((void)((B)->p < ((B)->buffer+LUAL_BUFFERSIZE) || luaL_prepbuffer(B)), \
    (*(B)->p++ = (char)(c))) // not tested

#define luaL_addsize(B,n)	((B)->p += (n)) // not tested

typedef void    (*lualinkerL_buffinit) (lua_State *L, luaL_Buffer *B); // not tested
typedef char*   (*lualinkerL_prepbuffer) (luaL_Buffer *B); // not tested
typedef void    (*lualinkerL_addlstring) (luaL_Buffer *B, const char *s, size_t l); // not tested
typedef void    (*lualinkerL_addstring) (luaL_Buffer *B, const char *s); // not tested
typedef void    (*lualinkerL_addvalue) (luaL_Buffer *B); // not tested
typedef void    (*lualinkerL_pushresult) (luaL_Buffer *B); // not tested

LUALIB_API lualinkerL_buffinit      luaL_buffinit;
LUALIB_API lualinkerL_prepbuffer    luaL_prepbuffer;
LUALIB_API lualinkerL_addlstring    luaL_addlstring;
LUALIB_API lualinkerL_addstring     luaL_addstring;
LUALIB_API lualinkerL_addvalue      luaL_addvalue;
LUALIB_API lualinkerL_pushresult    luaL_pushresult;

/* }====================================================== */


/*
** Compatibility macros and functions
*/
typedef int  (*lualinker_dofile) (lua_State *L, const char *filename);
typedef int  (*lualinker_dostring) (lua_State *L, const char *str);
typedef int  (*lualinker_dobuffer) (lua_State *L, const char *buff, size_t sz, const char *n);

LUALIB_API lualinker_dofile     lua_dofile;
LUALIB_API lualinker_dostring   lua_dostring;
LUALIB_API lualinker_dobuffer   lua_dobuffer;

#define luaL_check_lstr     luaL_checklstring
#define luaL_opt_lstr       luaL_optlstring 
#define luaL_check_number   luaL_checknumber 
#define luaL_opt_number     luaL_optnumber
#define luaL_arg_check      luaL_argcheck
#define luaL_check_string   luaL_checkstring
#define luaL_opt_string     luaL_optstring
#define luaL_check_int      luaL_checkint
#define luaL_check_long     luaL_checklong
#define luaL_opt_int        luaL_optint
#define luaL_opt_long       luaL_optlong

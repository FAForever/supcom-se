// See copyright notice in scse_copyright.txt

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SCSE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SCSE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SCSE_EXPORTS
#define SCSE_API __declspec(dllexport)
#else
#define SCSE_API __declspec(dllimport)
#endif

#ifndef SCSE_SCSELIBNAME
#define SCSE_SCSELIBNAME "scse"
#endif

// Link lua linker functions with SupCom lua functions and open scse library.
//
// Return to lua values:
// 1. Return to lua boolean value.
// If the function succeeds, the return value is true, otherwise false.
SCSE_API int luaopen_scse(lua_State *L);

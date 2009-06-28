========================================================================
    DYNAMIC LINK LIBRARY : scse Project Overview
========================================================================

AppWizard has created this scse DLL for you.

This file contains a summary of what you will find in each of the files that
make up your scse application.


scse.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

scse.cpp
    This is the main DLL source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named scse.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////

SOME NOTES FOR FUTURE:

CreateToolhelp32Snapshot - uses for reading loaded modules (see ms-help://MS.VSCC.v90/MS.MSDNQTR.v90.ru/dllproc/base/module_walking.htm)

GetProcAddress(lib, "?lua_resume@@YAHPAUlua_State@@H@Z"); - this is how to get address of function from dll which compiled without .def file


Function for testing recursion through Lua state:

static int scse_fib (lua_State *L)
{
    lua_Number n = lua_tonumber(L, 1);

    if (n < 2)
    {
        lua_pushnumber(L, n);
	    return 1;
    }

    lua_getglobal(L, "scse");
    lua_pushstring(L, "fib");
    lua_gettable(L, -2);
    lua_pushnumber(L, n * n / n - 1);
    lua_call(L, 1, 1); // scse.fib(n-1)
    lua_Number tmp = lua_tonumber(L, -1);

    lua_getglobal(L, "scse");
    lua_pushstring(L, "fib");
    lua_gettable(L, -2);
    lua_pushnumber(L, n * n / n - 2);
    lua_call(L, 1, 1); // scse.fib(n-2)
    tmp += lua_tonumber(L, -1);

    lua_pushnumber(L, tmp);
    return 1;
}

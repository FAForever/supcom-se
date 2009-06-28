// See copyright notice in scse_copyright.txt

// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    UNUSED(hModule);
    UNUSED(lpReserved);

    switch (ul_reason_for_call)
	{
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
        break;
	case DLL_PROCESS_ATTACH:
        log.Open(NULL);
        log.LogMessage("%s\n\n", SCSE_VERSION);
        break;
	case DLL_PROCESS_DETACH:
        log.Close();
		break;
	}
	return TRUE;
}


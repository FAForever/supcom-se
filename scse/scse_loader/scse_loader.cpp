// See copyright notice in scse_copyright.txt

// scse_loader.cpp : Defines the entry point for the console application.

#include "stdafx.h"

void CloseLoader(int result);
bool GetHookAddr(char *procFileName, UInt32 *hookAddr);
bool SetHook(PROCESS_INFORMATION *info, const UInt32 hookAddr);

int _tmain(int argc, _TCHAR* argv[])
{
    char *procFileName;
    UInt32 hookAddr;

    printf ("%s\n\n", SCSE_VERSION);

    appOptions.ReadArgs(argc, argv);

    if(appOptions.helpOnly)
    {
        CloseLoader(0);
    }

    if(File::Exists("ForgedAlliance.exe"))
    {
        procFileName = "ForgedAlliance.exe";
    }
    else if(File::Exists("SupremeCommander.exe"))
    {
        procFileName = "SupremeCommander.exe";
    }
    else
    {
        printf("ERROR! Couldn't find ForgedAlliance.exe or SupremeCommander.exe.\n");
        printf("Make sure you're running this from the same folder as EXE file.\n");
        CloseLoader(-1);
    }

    if(GetHookAddr(procFileName, &hookAddr))
    {
        if(appOptions.crcOnly)
            CloseLoader(0);

        // Create the process
        STARTUPINFO         startupInfo = { 0 };
        PROCESS_INFORMATION procInfo = { 0 };
        startupInfo.cb = sizeof(startupInfo);

        wchar_t *lpApplicationName = new wchar_t[strlen(procFileName)+1];
        size_t numOfCharConverted;
        mbstowcs_s(&numOfCharConverted, lpApplicationName, strlen(procFileName)+1, procFileName, strlen(procFileName));

        bool processCreated = CreateProcess(
            lpApplicationName,
            appOptions.haveArgs ? appOptions.procArgs : NULL,
            NULL,   // default process security
            NULL,   // default thread security
            TRUE,   // don't inherit handles
            CREATE_SUSPENDED,
            NULL,   // no new environment
            NULL,   // no new cwd
            &startupInfo,
            &procInfo) != 0;

        delete [] lpApplicationName;

        if(!processCreated)
        {
            if(GetLastError() == ERROR_ELEVATION_REQUIRED)
                printf("ERROR! Vista has decided that launching Supreme Commander requires UAC privilege elevation. There is no good reason for this to happen, but to fix it, right-click on LuaJITer.exe, go to Properties, pick the Compatibility tab, then turn on \"Run this program as an administrator\".\n");
            else
                printf("ERROR! Couldn't create process for %s (error code: %d).\n", procFileName, GetLastError());

            CloseLoader(-1);
        }

        // Enable calling luaopen_loadlib function
        bool hookSetted = SetHook(&procInfo, hookAddr);

        if(hookSetted)
        {
            printf("Resuming %s process.\n", procFileName);
            ResumeThread(procInfo.hThread);
        }
        else
        {
            printf("Terminating %s process.\n", procFileName);
            TerminateProcess(procInfo.hProcess, 0);
        }

        // Clean up
        CloseHandle(procInfo.hProcess);
        CloseHandle(procInfo.hThread);

        if(!hookSetted)
            CloseLoader(-1);
    }
    else
        CloseLoader(-1);

    CloseLoader(0);
}

void CloseLoader(int result)
{
    printf("Press any key...\n");
    getchar();
    exit(result);
}

bool GetHookAddr(char *procFileName, UInt32 *hookAddr)
{
    UInt32 checksum;

    if(Checksum::GetChecksum(procFileName, &checksum))
    {
        printf("%s checksum: 0x%08x.\n", procFileName, checksum);

        switch(checksum)
        {
        case 0x84b9e832: // Supreme Commander Forged Alliance 1.5.3599 official version
            printf("Finded Supreme Commander Forged Alliance 1.5.3599 version.\n");
            *hookAddr = 0x0090a3bd;
            printf("Address for hook: 0x%08x.\n", *hookAddr);
            return true;

        case 0xfd0f38a1: // Supreme Commander 1.1.3280 official version
            printf("Finded Supreme Commander 1.1.3280 version.\n");
            //*hookAddr = 0x013da87a;
            //printf("Address for hook: 0x%08x.\n", *hookAddr);
            printf("Supreme Commander 1.1.3280 not supported yet.\n", *hookAddr);
            return false;

        default: // unknown checksum
            printf("ERROR! You have an unknown version of Supreme Commander.\n");
            break;
        }
    }
    else
        printf("ERROR! Couldn't open %s (error code: %d).\n", procFileName, GetLastError());

    return false;
}

bool SetHook(PROCESS_INFORMATION *info, const UInt32 hookAddr)
{
    bool result = false;

    __try {
        printf("Setting hook at 0x%08x.\n", hookAddr);

        HANDLE process = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, info->dwProcessId);

        if(process != NULL)
        {
            // Before setting hook:
            // 75 ## jnz short offset
            
            // After setting hook:
            // 74 ## je short offset

            SIZE_T bytesCount;
            Byte hook[2];

            if(ReadProcessMemory(process, (LPVOID)(hookAddr), &hook, sizeof(hook), &bytesCount) != 0)
            {
                printf("Code before hooking: %02X %02X\n", hook[0], hook[1]);

                if(hook[0] == 0x75)
                {
                    hook[0] = 0x74;

                    if(WriteProcessMemory(process, (LPVOID)(hookAddr), &hook, sizeof(hook), &bytesCount) != 0)
                    {
                        FlushInstructionCache(process, NULL, 0);
                        ReadProcessMemory(process, (LPVOID)(hookAddr), &hook, sizeof(hook), &bytesCount);
                        printf("Code after hooking: %02X %02X\n", hook[0], hook[1]);

                        if(hook[0] == 0x74)
                        {
                            printf("Hook successefully setted.\n");
                            result = true;
                        }
                        else
                        {
                            printf("ERROR! Hook not setted.\n");
                            result = false;
                        }
                    }
                    else
                    {
                        printf("ERROR! Couldn't write to process memory (error code: %d).\n", GetLastError());
                        result = false;
                    }
                }
                else
                {
                    printf("ERROR! Wrong hook address. First command should be 75.\n");
                    result = false;
                }
            }
            else
            {
                printf("ERROR! Couldn't read process memory (error code: %d).\n", GetLastError());
                result = false;
            }

            CloseHandle(process);
        }
        else
        {
            printf("ERROR! Couldn't get process handle (error code: %d).\n", GetLastError());
            result = false;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        printf("ERROR! Couldn't set hook (error code: %d).\n", GetLastError());
        printf("In most cases, this is caused by an overly paranoid software antivirus package. Disabling either of these may solve the problem.\n");
        result = false;
    }

    return result;
}

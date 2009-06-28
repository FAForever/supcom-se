// See copyright notice in scse_copyright.txt

#include "stdafx.h"
#include "Options.h"

Options appOptions;

Options::Options(void)
{
    helpOnly = false;
    crcOnly = false;
    haveArgs = false;
}

Options::~Options(void)
{
}

void Options::ReadArgs(int argc, _TCHAR* argv[])
{
    if (argc > 1)
    {
        // Remove app name
        argc--;
        argv++;

        while(argc > 0)
        {
            _TCHAR *arg = *argv++;
            argc--;

            if((arg[0] == '-') || (arg[0] == '/'))
            {
                arg++;

                if((_wcsicmp(arg, L"?") == 0) || (_wcsicmp(arg, L"h") == 0) || (_wcsicmp(arg, L"help") == 0))
                {
                    helpOnly = true;
                    printf("Usage: scse_loader [options]\n");
                    printf("Options starts with '-' or '/' (example: -help or /help)\n\n");
                    printf("Options list:\n");
                    printf("  ?, h, help - print this options list, don't launch anything\n");
                    printf("  crc, crconly - just print the checksum of the EXE, don't launch anything\n");
                    printf("  args \"command line\" - pass the command line to process\n");
                    printf("                        example: args \"/showlog /windowed 1024 768\"\n");
                    printf("\n");
                }
                if((_wcsicmp(arg, L"crc") == 0) || (_wcsicmp(arg, L"crconly") == 0))
                {
                    crcOnly = true;
                }
                if((_wcsicmp(arg, L"args") == 0))
                {
                    _TCHAR *arg = *argv++;
                    argc--;

                    wcscpy_s(procArgs, sizeof(procArgs) / sizeof(_TCHAR), L"\"");
                    _wgetcwd(&procArgs[1], sizeof(procArgs) / sizeof(_TCHAR));
                    wcscat_s(procArgs, sizeof(procArgs) / sizeof(_TCHAR), L"\\\" ");
                    wcscat_s(procArgs, sizeof(procArgs) / sizeof(_TCHAR), arg);
                    haveArgs = true;
                }
            }
        }
    }
}

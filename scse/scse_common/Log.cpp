// See copyright notice in scse_copyright.txt

#include "StdAfx.h"
#include "Log.h"

Log log;

Log::Log(void)
{
    logFile = NULL;
}

Log::~Log(void)
{
    if(logFile != NULL)
        Log::Close();
}

bool Log::Open(char *logName)
{
    logFile = _fsopen(logName == NULL ? "scse.log" : logName, "w", _SH_DENYWR);
    if(logFile != NULL)
    {
        formatBuf = new char[FORMATBUF_SIZE];
        return true;
    }
    else
        return false;
}

void Log::Close(void)
{
    if(logFile != NULL)
    {
        fclose(logFile);
        delete [] formatBuf;
    }
}

void Log::LogMessage(const char *fmt, ...)
{
	va_list	argList;

	va_start(argList, fmt);
    vsprintf_s(formatBuf, FORMATBUF_SIZE, fmt, argList);
	va_end(argList);
    fprintf(logFile, formatBuf);
    fflush(logFile);
}

void Log::LogError(const char *fmt, ...)
{
	va_list	argList;

	va_start(argList, fmt);
    vsprintf_s(formatBuf, FORMATBUF_SIZE, fmt, argList);
	va_end(argList);
    fprintf(logFile, formatBuf);
    fprintf(logFile, "Error code: %d.\n", GetLastError());
    fflush(logFile);
}

// See copyright notice in scse_copyright.txt

#pragma once

#define FORMATBUF_SIZE 4096

class Log
{
public:
    Log(void);
    ~Log(void);
    bool Open(char *logName);
    void Close(void);
    void LogMessage(const char *fmt, ...);
    void LogError(const char *fmt, ...);
private:
    FILE *logFile;
    char *formatBuf;
};

extern Log log;
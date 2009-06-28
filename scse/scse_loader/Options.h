// See copyright notice in scse_copyright.txt

#pragma once

class Options
{
public:
    Options(void);
    ~Options(void);
    void ReadArgs(int argc, _TCHAR* argv[]);
    bool helpOnly;
    bool crcOnly;
    bool haveArgs;
    _TCHAR procArgs[1024];
};

extern Options appOptions;

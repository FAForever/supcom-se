// See copyright notice in scse_copyright.txt

#include "stdafx.h"
#include "File.h"

bool File::Exists(char *filePath)
{
    bool result = false;
    FILE *file;

    errno_t err = fopen_s(&file, filePath, "rb");

    if(err == 0)
    {
        result = true;
        fclose(file);
    }

    return result;
}
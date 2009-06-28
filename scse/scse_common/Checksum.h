// See copyright notice in scse_copyright.txt

#pragma once

class Checksum
{
public:
    static bool GetChecksum(char *procFileName, UInt32 *checksum);
    static UInt32 Crc32(Byte *buf, long len);
};

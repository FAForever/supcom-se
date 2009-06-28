// See copyright notice in scse_copyright.txt

#include "StdAfx.h"
#include "Checksum.h"

bool Checksum::GetChecksum(char *procFileName, UInt32 *checksum)
{
    Byte *buf;
    long bufSize;
    FILE *file;

    errno_t err = fopen_s(&file, procFileName, "rb");

    if(err != 0)
        return false;

    fseek(file, 0, SEEK_END);
    bufSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    buf = new Byte[bufSize];

    fread(buf, 1, bufSize, file);

    fclose(file);

    *checksum = Checksum::Crc32(buf, bufSize);

    delete [] buf;

    return true;
}

// Code from wikipedia, slightly less than half free encyclopedia =)
// Name  : CRC-32
// Poly  : 0x04C11DB7    x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 
//                    + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
// Init  : 0xFFFFFFFF
// Revert: true
// XorOut: 0xFFFFFFFF
// Check : 0xCBF43926 ("123456789")
// MaxLen: 268 435 455 bytes (2 147 483 647 bits)
UInt32 Checksum::Crc32(Byte *buf, long len)
{
    unsigned long crc_table[256];
    unsigned long crc;
 
    for (int i = 0; i < 256; i++)
    {
        crc = i;
        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
 
        crc_table[i] = crc;
    };
 
    crc = 0xFFFFFFFFUL;
 
    while (len--) 
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
 
    return (UInt32)(crc ^ 0xFFFFFFFFUL);
}

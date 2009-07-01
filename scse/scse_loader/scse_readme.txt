Supreme Commander Script Extender by Mesenion.

### Installation ###

1. Copy "scse_loader.exe" and "scse.dll" to folder with ForgedAlliance.exe application.
For example, this folder is "C:\Program Filess\Gas Powered Games\Supreme Commander - Forged Alliance\bin\".

2. Copy "00 SupCom FA 1.5.3599.scd" to gamedata folder for Supreme Commander.
For example, this folder is "C:\Program Filess\Gas Powered Games\Supreme Commander - Forged Alliance\gamedata\".

3. Launch "scse_loader.exe".


### Command arguments for scse_loader ###

Usage: scse_loader [options]
Options starts with '-' or '/' (example: -help or /help)

Options list:
  ?, h, help - print this options list, don't launch anything
  crc, crconly - just print the checksum of the EXE, don't launch anything
  args "command line" - pass the command line to process
                        example: args "/showlog /windowed 1024 768"


### Changelog ###

1.0.0.2 - alpha version (http://code.google.com/p/supcom-se/source/browse/?r=4).

Added almost all Lua functions.
Enabled io and os libs in Lua scripts.


1.0.0.1 - pre-alpha version (http://code.google.com/p/supcom-se/source/browse/?r=3).

First public concept version of SCSE.
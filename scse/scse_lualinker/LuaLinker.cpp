// See copyright notice in scse_copyright.txt

#include "StdAfx.h"
#include "LuaLinker.h"

bool LuaLinker::Link(void)
{
    UInt32 checksum;
    char procFileName[4096];

    if(GetModuleFileNameExA(GetCurrentProcess(), NULL, procFileName, 4096) == 0)
    {
        log.LogError("ERROR! Couldn't get process image file name.\n");
        return false;
    }

    if(Checksum::GetChecksum(procFileName, &checksum))
    {
        UInt32 base = 0; // TODO: check base address of the module in the context of the owning process

        log.LogMessage("%s checksum: 0x%08x.\n", procFileName, checksum);

        switch(checksum)
        {
        case 0x84b9e832: // Supreme Commander Forged Alliance 1.5.3599 official version
            log.LogMessage("Finded Supreme Commander Forged Alliance 1.5.3599 version.\n");

            // ----------
            // lua.h
            // ----------

            /*
            ** access functions (stack -> C)
            */
            lua_isnumber    = (lualinker_isnumber)(base + 0x0090C000);
            lua_isstring    = (lualinker_isstring)(base + 0x0090C060);
            //lua_iscfunction = (lualinker_iscfunction)(base + 0x); // SupCom haven't definition for this function
            lua_isuserdata  = (lualinker_isuserdata)(base + 0x0090C0B0);
            lua_type        = (lualinker_type)(base + 0x0090BFA0);
            lua_typename    = (lualinker_typename)(base + 0x0090BFE0);

            lua_equal       = (lualinker_equal)(base + 0x0090C160);
            lua_rawequal    = (lualinker_rawequal)(base + 0x0090C0F0);
            lua_lessthan    = (lualinker_lessthan)(base + 0x0090C1E0);

            lua_tonumber    = (lualinker_tonumber)(base + 0x0090C250);
            lua_toboolean   = (lualinker_toboolean)(base + 0x0090C2A0);
            lua_tostring    = (lualinker_tostring)(base + 0x0090C2F0);
            lua_strlen      = (lualinker_strlen)(base + 0x0090C370);
            lua_tocfunction = (lualinker_tocfunction)(base + 0x0090C3D0);
            lua_touserdata  = (lualinker_touserdata)(base + 0x0090C410);
            lua_tothread    = (lualinker_tothread)(base + 0x0090C4B0);
            lua_topointer   = (lualinker_topointer)(base + 0x0090C4F0);

            /*
            ** push functions (C -> stack)
            */
            lua_pushnil             = (lualinker_pushnil)(base + 0x0090C560);
            lua_pushnumber          = (lualinker_pushnumber)(base + 0x0090C5A0);
            lua_pushlstring         = (lualinker_pushlstring)(base + 0x0090C5E0);
            lua_pushstring          = (lualinker_pushstring)(base + 0x0090C650);
            lua_pushvfstring        = (lualinker_pushvfstring)(base + 0x0090C6B0);
            lua_pushfstring         = (lualinker_pushfstring)(base + 0x0090C6F0);
            lua_pushcclosure        = (lualinker_pushcclosure)(base + 0x0090C730);
            lua_pushboolean         = (lualinker_pushboolean)(base + 0x0090C7E0);
            lua_pushlightuserdata   = (lualinker_pushlightuserdata)(base + 0x0090C820);

            /*
            ** get functions (Lua -> stack)
            */
            lua_gettable    = (lualinker_gettable)(base + 0x0090C860);

            /*
            ** `load' and `call' functions (load and run Lua code)
            */
            lua_call    = (lualinker_call)(base + 0x0090CC60);

            // ----------
            // lauxlib.h
            // ----------

            luaL_openlib        = (lualinkerL_openlib)(base + 0x0090D660);
            luaL_checklstring   = (lualinkerL_checklstring)(base + 0x0090E300);

            return true;
        default: // unknown checksum
            log.LogMessage("ERROR! You have an unknown version of Supreme Commander.\n");
            break;
        }
    }

    return false;
}

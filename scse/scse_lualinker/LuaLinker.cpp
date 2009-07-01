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
            ** state manipulation
            */
            lua_open        = (lualinker_open)(base + 0x00923F20);
            lua_close       = (lualinker_close)(base + 0x00923C30);
            lua_newthread   = (lualinker_newthread)(base + 0x0090BD90);

            //lua_atpanic     = (lualinker_atpanic)(base + 0x); // SupCom haven't definition for this function

            /*
            ** basic stack manipulation
            */
            lua_gettop      = (lualinker_gettop)(base + 0x0090BDF0);
            lua_settop      = (lualinker_settop)(base + 0x0090BE00);
            lua_pushvalue   = (lualinker_pushvalue)(base + 0x0090BF40);
            lua_remove      = (lualinker_remove)(base + 0x0090BE50);
            lua_insert      = (lualinker_insert)(base + 0x0090BEA0);
            lua_replace     = (lualinker_replace)(base + 0x0090BEF0);
            lua_checkstack  = (lualinker_checkstack)(base + 0x0090BCC0);

            lua_xmove       = (lualinker_xmove)(base + 0x0090BD20);

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
            //lua_touserdata  = (lualinker_touserdata)(base + 0x0090C410); // SupCom haven't definition for this function (actually SupCom have lua_touserdata with different syntax)
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
            lua_gettable        = (lualinker_gettable)(base + 0x0090C860);
            lua_rawget          = (lualinker_rawget)(base + 0x0090C8B0);
            lua_rawgeti         = (lualinker_rawgeti)(base + 0x0090C900);
            lua_newtable        = (lualinker_newtable)(base + 0x0090C970);
            //lua_newuserdata     = (lualinker_newuserdata)(base + 0x0090D040); // SupCom haven't definition for this function (actually SupCom have lua_newuserdata with different syntax)
            lua_getmetatable    = (lualinker_getmetatable)(base + 0x0090C9E0);
            lua_getfenv         = (lualinker_getfenv)(base + 0x0090CA50);

            /*
            ** set functions (stack -> Lua)
            */
            lua_settable        = (lualinker_settable)(base + 0x0090CAC0);
            lua_rawset          = (lualinker_rawset)(base + 0x0090CB00);
            lua_rawseti         = (lualinker_rawseti)(base + 0x0090CB50);
            lua_setmetatable    = (lualinker_setmetatable)(base + 0x0090CBA0);
            lua_setfenv         = (lualinker_setfenv)(base + 0x0090CC10);

            /*
            ** `load' and `call' functions (load and run Lua code)
            */
            lua_call    = (lualinker_call)(base + 0x0090CC60);
            lua_pcall   = (lualinker_pcall)(base + 0x0090CC90);
            lua_cpcall  = (lualinker_cpcall)(base + 0x0090CD30);
            lua_load    = (lualinker_load)(base + 0x0090CE20);
            lua_dump    = (lualinker_dump)(base + 0x0090CE70);

            /*
            ** coroutine functions
            */
            lua_yield   = (lualinker_yield)(base + 0x009136A0);
            lua_resume  = (lualinker_resume)(base + 0x00913E60);

            /*
            ** garbage-collection functions
            */
            lua_getgcthreshold  = (lualinker_getgcthreshold)(base + 0x0090CEB0);
            lua_getgccount      = (lualinker_getgccount)(base + 0x0090CEC0);
            lua_setgcthreshold  = (lualinker_setgcthreshold)(base + 0x0090CED0);

            /*
            ** miscellaneous functions
            */
            lua_version = (lualinker_version)(base + 0x0090CF10);
            lua_error   = (lualinker_error)(base + 0x0090CF20);
            lua_next    = (lualinker_next)(base + 0x0090CF30);
            lua_concat  = (lualinker_concat)(base + 0x0090CFA0);

            /*
            ** compatibility functions
            */
            lua_pushupvalues = (lualinker_pushupvalues)(base + 0x0090D140);

            /*
            ** Debug API
            */
            lua_getstack    = (lualinker_getstack)(base + 0x00911E40);
            lua_getinfo     = (lualinker_getinfo)(base + 0x00912B50);
            lua_getlocal    = (lualinker_getlocal)(base + 0x00911EE0);
            lua_setlocal    = (lualinker_setlocal)(base + 0x00911F50);
            lua_getupvalue  = (lualinker_getupvalue)(base + 0x0090D200);
            lua_setupvalue  = (lualinker_setupvalue)(base + 0x0090D260);

            lua_sethook         = (lualinker_sethook)(base + 0x00911DC0);
            lua_gethook         = (lualinker_gethook)(base + 0x00911E10);
            lua_gethookmask     = (lualinker_gethookmask)(base + 0x00911E20);
            lua_gethookcount    = (lualinker_gethookcount)(base + 0x00911E30);

            // ----------
            // lauxlib.h
            // ----------

            luaL_openlib        = (lualinkerL_openlib)(base + 0x0090D660);
            luaL_getmetafield   = (lualinkerL_getmetafield)(base + 0x0090D5A0);
            luaL_callmeta       = (lualinkerL_callmeta)(base + 0x0090D600);
            luaL_typerror       = (lualinkerL_typerror)(base + 0x0090E200);
            luaL_argerror       = (lualinkerL_argerror)(base + 0x0090E160);
            luaL_checklstring   = (lualinkerL_checklstring)(base + 0x0090E300);
            luaL_optlstring     = (lualinkerL_optlstring)(base + 0x0090E370);
            luaL_checknumber    = (lualinkerL_checknumber)(base + 0x0090E3D0);
            luaL_optnumber      = (lualinkerL_optnumber)(base + 0x0090E450);

            luaL_checkstack     = (lualinkerL_checkstack)(base + 0x0090D570);
            luaL_checktype      = (lualinkerL_checktype)(base + 0x0090E280);
            luaL_checkany       = (lualinkerL_checkany)(base + 0x0090E2D0);

            luaL_newmetatable   = (lualinkerL_newmetatable)(base + 0x0090D4D0);
            luaL_getmetatable   = (lualinkerL_getmetatable)(base + 0x0090D550);
            //luaL_checkudata     = (lualinkerL_checkudata)(base + 0x); // SupCom haven't definition for this function

            luaL_where  = (lualinkerL_where)(base + 0x0090D3E0);
            luaL_error  = (lualinkerL_error)(base + 0x0090D450);

            luaL_findstring = (lualinkerL_findstring)(base + 0x0090D480);

            luaL_ref    = (lualinkerL_ref)(base + 0x0090DC80);
            luaL_unref  = (lualinkerL_unref)(base + 0x0090DD50);

            luaL_getn   = (lualinkerL_getn)(base + 0x0090D8F0);
            luaL_setn   = (lualinkerL_setn)(base + 0x0090D810);

            luaL_loadfile   = (lualinkerL_loadfile)(base + 0x0090DE30); // code have changes in FA
            luaL_loadbuffer = (lualinkerL_loadbuffer)(base + 0x0090DFC0);

            /*
            ** Generic Buffer manipulation
            */
            luaL_buffinit   = (lualinkerL_buffinit)(base + 0x0090DC60);
            luaL_prepbuffer = (lualinkerL_prepbuffer)(base + 0x0090DAC0);
            luaL_addlstring = (lualinkerL_addlstring)(base + 0x0090DB00);
            luaL_addstring  = (lualinkerL_addstring)(base + 0x0090DB60);
            luaL_addvalue   = (lualinkerL_addvalue)(base + 0x0090DBD0);
            luaL_pushresult = (lualinkerL_pushresult)(base + 0x0090DB90);

            /*
            ** Compatibility functions
            */
            lua_dofile      = (lualinker_dofile)(base + 0x0090E090);
            lua_dostring    = (lualinker_dostring)(base + 0x0090E130);
            lua_dobuffer    = (lualinker_dobuffer)(base + 0x0090E0D0);

            // ----------
            // lualib.h
            // ----------

            luaopen_io = (lualinkeropen_io)(base + 0x00917410);

            return true;
        default: // unknown checksum
            log.LogMessage("ERROR! You have an unknown version of Supreme Commander.\n");
            break;
        }
    }

    return false;
}

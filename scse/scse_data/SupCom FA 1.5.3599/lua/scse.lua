# You should use loadlib function before defenition __index metamethod in globalsmeta
# (defined in /lua/system/config.lua). Metamethod __index causes an error message when a nonexistent
# global is accessed. But when loadlib register table of lib functions it checks whether
# table already exists and causes error.

if loadlib ~= nil then
    local open_scse = loadlib("scse.dll", "luaopen_scse")
    open_scse()

    WARN(scse.version())

    # Open io and os libs
    scse.luaopen_io()
end
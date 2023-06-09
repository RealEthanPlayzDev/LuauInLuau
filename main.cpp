#include "lua.h"
#include "lualib.h"
#include "luacode.h"
#include "Luau/Common.h"
#include "Luau/ExperimentalFlags.h"
#include <string>

LUAU_NOINLINE int LuauRunUsingCustomState(lua_State* L, const char* bytecode)
{
    std::string BytecodeStdString = bytecode;
    int LoadResult = luau_load(L, "LuauInLuau_Chunk", bytecode, BytecodeStdString.size(), 0);
    if (LoadResult == 1) { return 1; }
    return lua_pcall(L, 0, 0, 0);
}

LUAU_NOINLINE bool SetLuauFlag(std::string name, bool state)
{
    for (Luau::FValue<bool>* flag = Luau::FValue<bool>::list; flag; flag = flag->next)
    {
        if (name == flag->name)
        {
            flag->value = state;
            return true;
        }
    }
    return false;
}

LUAU_NOINLINE void SetLuauFlags(bool state)
{
    for (Luau::FValue<bool>* flag = Luau::FValue<bool>::list; flag; flag = flag->next)
        if (strncmp(flag->name, "Luau", 4) == 0)
            flag->value = state;
}

LUAU_NOINLINE void SetLuauFlagsDefault()
{
    for (Luau::FValue<bool>* flag = Luau::FValue<bool>::list; flag; flag = flag->next)
        if (strncmp(flag->name, "Luau", 4) == 0 && !Luau::isFlagExperimental(flag->name))
            flag->value = true;
}

int main()
{
    return 0;
}
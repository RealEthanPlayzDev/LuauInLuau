#include "lua.h"
#include "lualib.h"
#include "luacode.h"
#include <string.h>
#include <string>

extern "C" char* LuauCompile(const char* src)
{
    size_t BytecodeSize;
    return luau_compile(src, strlen(src), nullptr, &BytecodeSize);
}

extern "C" int LuauRunUsingCustomState(lua_State* L, const char* bytecode)
{
    std::string BytecodeStdString = bytecode;
    int LoadResult = luau_load(L, "LuauInLuau_Chunk", bytecode, BytecodeStdString.size(), 0);
    if (LoadResult == 1) { return 1; }
    return lua_pcall(L, 0, 0, 0);
}

extern "C" int LuauRun(const char* bytecode)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    int Result = LuauRunUsingCustomState(L, bytecode);
    lua_close(L);
    return Result;
}

extern "C" int LuauRunWithSafeEnv(const char* bytecode)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_sandbox(L);
    int Result = LuauRunUsingCustomState(L, bytecode);
    lua_close(L);
    return Result;
}

int main()
{
    const char* Bytecode = LuauCompile("print(\"hello world\")");
    LuauRun(Bytecode);
    LuauRunWithSafeEnv(Bytecode);
    return 0;
}
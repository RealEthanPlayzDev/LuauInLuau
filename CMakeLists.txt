cmake_minimum_required(VERSION 3.20)
project(LuauInLuau LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

option(LUAU_BUILD_CLI "Build CLI" OFF)
option(LUAU_BUILD_TESTS "Build tests" OFF)
option(LUAU_BUILD_WEB "Build Web module" OFF)
option(LUAU_WERROR "Warnings as errors" OFF)
option(LUAU_STATIC_CRT "Link with the static CRT (/MT)" OFF)
add_subdirectory(luau)

add_executable(LuauInLuau main.cpp)
target_link_libraries(LuauInLuau Luau.Compiler)
target_link_libraries(LuauInLuau Luau.VM)
cmake_minimum_required (VERSION 3.26)


if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-g -Wall -Wextra -Wpedantic -fPIC)
endif()    

set (CMAKE_CXX_STANDARD 23)

project (Linux-Debugger CXX)

add_subdirectory (Linux-Debugger)
add_subdirectory (Examples)
cmake_minimum_required (VERSION 3.26)


add_compile_options("-Wall")
set (CMAKE_CXX_STANDARD 23)

project (Linux-Debugger CXX)

add_subdirectory (Linux-Debugger)
add_subdirectory (Examples)
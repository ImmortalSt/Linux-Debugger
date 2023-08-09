
add_executable(HWCounter "Hardware Breakpoint/Counter/Breakpoint.cpp")
target_link_libraries(HWCounter PRIVATE Linux-Debugger-shared)

add_executable(HWHelloWorld "Hardware Breakpoint/HelloWorld/BreakpointREADWRITE.cpp")
target_link_libraries(HWHelloWorld PRIVATE Linux-Debugger-shared)



add_executable(SFCounter "Software Breakpoint/Counter/Breakpoint.cpp")
target_link_libraries(SFCounter PRIVATE Linux-Debugger-shared)

add_executable(SFHelloWorld "Software Breakpoint/HelloWorld/Breakpoint.cpp")
target_link_libraries(SFHelloWorld PRIVATE Linux-Debugger-shared)
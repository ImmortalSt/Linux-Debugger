


add_library(Linux-Debugger-obj OBJECT
    "SmartDescriptor/SmartDescriptor.h"
    "Process/Process.h"
    "Process/Process.cpp"
    "Process/Module/Maps.h"
    "Process/Module/Maps.cpp"
    "Process/Module/Module.h"
    "Process/Thread/Thread.h"
    "Process/Thread/Thread.cpp"
    "Process/Thread/ThreadList.h"
    "Process/Thread/ThreadList.cpp"
    "Process/Debugger/Registers.h"
    "Process/Debugger/DebuggerBase.h"
    "Process/Debugger/DebuggerBase.cpp"
    "Process/Debugger/HardwareDebugger/HardwareDebugger.h"
    "Process/Debugger/HardwareDebugger/HardwareDebugger.cpp"
    "Process/Debugger/SoftwareDebugger/SoftwareDebugger.h"
    "Process/Debugger/SoftwareDebugger/SoftwareDebugger.cpp"
)

add_library(Linux-Debugger-static STATIC $<TARGET_OBJECTS:Linux-Debugger-obj>)
add_library(Linux-Debugger-shared SHARED $<TARGET_OBJECTS:Linux-Debugger-obj>)
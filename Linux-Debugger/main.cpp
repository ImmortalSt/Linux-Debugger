#include <bits/types/struct_iovec.h>
#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "Process/Process.h"
#include "SmartDescriptor/SmartDescriptor.h"
#include <sys/ptrace.h>
#include <linux/elf.h>

void Observer(context context) {
    std::cout << context.rsi << '\n';
}


int main() {
   
    dbg::Process proc("./a.out");
    proc.threads._threads[0].EnableDebugging();
    uint64_t addr = proc.maps.GetBaseAddress() + 0x115D;

    proc.threads._threads[0].GetHardwareDebugger().SetBreakpoint(addr, HardwareDebugger::condition::EXEC, 1, &Observer);
    
    
    proc.threads._threads[0].GetHardwareDebugger().StartDebugLoop();

    perror("dd");
    int h = 0;
} 
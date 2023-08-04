#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "Process/Process.h"
#include "SmartDescriptor/SmartDescriptor.h"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>

void Observer(context context) {
    std::cout << context.rip << '\n';
}

int main() {
   
    dbg::Process proc("./a.out");
    proc.threads._threads[0].EnableDebugging();
    uint64_t addr = proc.maps.GetBaseAddress() + 0x1147;
    proc.threads._threads[0].GetHardwareDebugger().SetBreakpoint(addr, HardwareDebugger::condition::EXEC, 1, &Observer);

    for (int i = 0; i < 8; i++)
        std::cout << " Dr" << i << ": " << std::hex << proc.threads._threads[0].GetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * i)) << '\n';

    perror("dd");
    int h = 0;
} 
#include "../../../Linux-Debugger/Process/Process.h"

void Observer(context context) {
    std::cout << context.rip << '\n';
}


int main() {
    std::cout << "Starting..." << '\n';
    dbg::Process proc("./HelloWorld.out");
    if (proc.GetPid() == 0) {
        std::cout << "Start HelloWorld program.";
        return 1;
    }
    proc.threads._threads[0].EnableDebugging();
    uint64_t addr = proc.maps.GetBaseAddress() + 0x2004;
    proc.threads._threads[0].GetHardwareDebugger().SetBreakpoint(addr, HardwareDebugger::condition::RW, 1, &Observer);    
    proc.threads._threads[0].GetHardwareDebugger().StartDebugLoop();

    perror("dd");
} 
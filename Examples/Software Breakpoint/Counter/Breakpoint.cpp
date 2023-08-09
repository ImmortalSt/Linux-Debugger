#include "../../../Linux-Debugger/Process/Process.h"

void Observer(context context) {
    std::cout << context.rsi << '\n';
}


int main() {
    std::cout << "Starting..." << '\n';
    dbg::Process proc("./Counter.out");
    if (proc.GetPid() == 0) {
        std::cout << "Start Counter program.";
        return 1;
    }
    proc.threads._threads[0].EnableDebugging();
    uint64_t addr = proc.maps.GetBaseAddress() + 0x115D;
    proc.threads._threads[0].GetSoftwareDebugger().SetBreakpoint(addr, SoftwareDebugger::condition::EXEC, 1, &Observer);    
    proc.threads._threads[0].GetSoftwareDebugger().StartDebugLoop();

    perror("dd");
} 
#include "../../../Linux-Debugger/Process/Process.h"

dbg::Process proc;
void Observer(context context) {
    std::cout << proc.ReadString(context.rax) << '\n';
}


int main() {

    proc = dbg::Process("./HelloWorld.out");
    std::cout << "Starting..." << '\n';
    if (proc.GetPid() == 0) {
        std::cout << "Start HelloWorld program.";
        return 1;
    }
    proc.threads._threads[0].EnableDebugging();
    uint64_t addr = proc.maps.GetBaseAddress() + 0x1144;
    proc.threads._threads[0].GetSoftwareDebugger().SetBreakpoint(addr, SoftwareDebugger::condition::EXEC, 1, &Observer);    
    proc.threads._threads[0].GetSoftwareDebugger().StartDebugLoop();

    perror("dd");
} 
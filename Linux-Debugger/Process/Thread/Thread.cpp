#include "Thread.h"

Thread::Thread(uint64_t pid) {
    _pid = pid;
    _hardwareDebugger = HardwareDebugger(pid);
}
Thread::~Thread() {}

context Thread::GetContext() {
    context regs{0};
    ptrace(PTRACE_GETREGS, _pid, 0, &regs);
    return regs;
}

void Thread::EnableDebugging() {
    int status;
    if (ptrace(PTRACE_ATTACH, _pid, nullptr, nullptr) == -1) {
        perror("ptrace PTRACE_ATTACH");
    }

    // Wait for the tracee to stop (i.e., the target thread stops)
    if (waitpid(_pid, &status, 0) == -1) {
        perror("waitpid");
    }
    _isDebugging = true;
}

void Thread::DisableDebugging(){
    if (ptrace(PTRACE_DETACH, _pid, nullptr, nullptr) == -1) {
        perror("ptrace PTRACE_DETACH");
    }
    _isDebugging = true;
}

void Thread::SetRegister(x64userStructOffsets offset, long long value){
    if(ptrace(PTRACE_POKEUSER, _pid, offset, value)  != 0) {
        perror("ptrace PTRACE_POKEUSER");
    }
}
long long Thread::GetRegister(x64userStructOffsets offset) {
    return ptrace(PTRACE_PEEKUSER, _pid, offset, 0);
}

HardwareDebugger& Thread::GetHardwareDebugger() {
    return _hardwareDebugger;
}
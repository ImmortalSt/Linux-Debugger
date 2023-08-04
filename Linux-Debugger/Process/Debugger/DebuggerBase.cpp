#include "DebuggerBase.h"
#include <cstdio>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/syscall.h>

void DebuggerBase::SetRegister(x64userStructOffsets offset, long long value){
    if(ptrace(PTRACE_POKEUSER, _pid, offset, value)  != 0) {
        perror("ptrace PTRACE_POKEUSER");
    }
}
long long DebuggerBase::GetRegister(x64userStructOffsets offset) {
    return ptrace(PTRACE_PEEKUSER, _pid, offset, 0);
}
struct user_regs_struct DebuggerBase::GetContext() {
    struct user_regs_struct regs{0};
    ptrace(PTRACE_GETREGS, _pid, 0, &regs);
    return regs;
}
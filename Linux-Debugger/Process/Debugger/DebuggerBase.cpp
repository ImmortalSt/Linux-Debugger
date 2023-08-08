#include "DebuggerBase.h"


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
int DebuggerBase::SetContext(struct user_regs_struct context) {
    if (ptrace(PTRACE_SETREGS, _pid, NULL, &context) == -1) {
            perror("ptrace PTRACE_SETREGS");
            return 1;
    }
    return 0;
}


int DebuggerBase::WaitException() {
    int status = 0;
    if(ptrace(PTRACE_CONT, _pid, NULL, NULL) != 0) {
        perror("ptrace PTRACE_CONT");
        return 0;
    }
    waitpid(_pid, &status, 0);
    return status;
}



int DebuggerBase::DoDebugStep() {
    int status = 0;
    ptrace(PTRACE_SINGLESTEP, _pid, 0, 0);
    waitpid(_pid, &status, 0);

    return status;
}
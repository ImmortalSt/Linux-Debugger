#ifndef _DEBUGGERBASE_
#define _DEBUGGERBASE_
#include <cstdint>
#include <sys/user.h>
#include "Registers.h"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <iostream>
#include "../../SmartDescriptor/SmartDescriptor.h"

typedef void (*context_function)(struct user_regs_struct);

class DebuggerBase {
public:
    DebuggerBase(uint64_t pid) : _pid(pid) {}
    ~DebuggerBase() {}
    virtual int SetBreakpoint(uint64_t address, uint8_t condition, uint16_t size, void (*observer)(struct user_regs_struct regs)) = 0;
    virtual int DelBreakpoint(uint64_t address) = 0;
    virtual void StartDebugLoop() = 0;

    template <typename T> T Read(uint64_t address) {
        T value = 0;
        SmartDescriptor<FILE*> mem(fopen(("/proc/" + std::to_string(_pid) + "/mem").c_str(), "rb"));
        fseek(mem, address, SEEK_SET);
        fread(&value, sizeof(T), 1, mem);
        return value;
    }
    template <typename T> void Write(uint64_t address, T value) {
        SmartDescriptor<FILE*> mem(fopen(("/proc/" + std::to_string(_pid) + "/mem").c_str(), "wb"));
        fseek(mem, address, SEEK_SET);
        fwrite(&value, sizeof(T), 1, mem);
    }


protected:
    uint64_t _pid;
    struct user_regs_struct GetContext();
    int SetContext(struct user_regs_struct context);
    void SetRegister(x64userStructOffsets offset, long long value);
    long long int GetRegister(x64userStructOffsets offset);
    int WaitException();
    int DoDebugStep();
};

#endif
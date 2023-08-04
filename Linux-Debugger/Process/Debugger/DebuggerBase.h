
#include <cstdint>
#include <sys/user.h>
#include "Registers.h"

class DebuggerBase {
public:
    DebuggerBase(uint64_t pid) : _pid(pid) {}
    ~DebuggerBase() {}
    virtual int SetBreakpoint(uint64_t address, uint8_t condition, uint16_t size, void (*observer)(struct user_regs_struct regs)) = 0;
    virtual int DelBreakpoint(uint64_t address) = 0;
    virtual void StartDebugLoop() = 0;

protected:
    uint64_t _pid;
    struct user_regs_struct GetContext();
    void SetRegister(x64userStructOffsets offset, long long value);
    long long int GetRegister(x64userStructOffsets offset);
};
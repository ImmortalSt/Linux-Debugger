#include "../DebuggerBase.h"
#include <iostream>
#include <vector>

class SoftwareDebugger final : public DebuggerBase {
public:
    enum condition {
        EXEC = 1
    };
    
    SoftwareDebugger() : DebuggerBase(0) {}
    SoftwareDebugger(uint64_t pid) : DebuggerBase(pid) {}

    int SetBreakpoint(uint64_t address, uint8_t condition, uint16_t size, void (*observer)(struct user_regs_struct regs)) override;
    int DelBreakpoint(uint64_t address) override;
    void StartDebugLoop() override;
private:
    
    typedef struct breakpointTAG
    {
        uint8_t oldByte;
        uint64_t address;
        context_function observer;
    } breakpoint;

    std::vector<breakpoint> _breakpoints;

    int WriteByte(uint64_t address, uint8_t byte);
    uint8_t ReadByte(uint64_t address);
};
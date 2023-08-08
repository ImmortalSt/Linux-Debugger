#include "../DebuggerBase.h"
#include <functional>
#include <iostream>
#include <array>
#include <sys/user.h>


class HardwareDebugger final : public DebuggerBase {
public:
    enum condition {
        EXEC = 0,
        WO = 1,
        PORT = 2,
        RW = 3
    };

    HardwareDebugger() : DebuggerBase(0) {}
    HardwareDebugger(uint64_t pid);
    ~HardwareDebugger();

    int SetBreakpoint(uint64_t address, uint8_t condition, uint16_t size, void (*observer)(struct user_regs_struct regs)) override;
    int DelBreakpoint(uint64_t address) override;
    void StartDebugLoop() override;

private:
    typedef struct breakpointTAG {
        uint64_t address = 0;
        context_function observer = 0;
    } breakpoint;

    std::array<breakpoint, 4> _breakpoints;
    
    void ClearBreakpoints();
};
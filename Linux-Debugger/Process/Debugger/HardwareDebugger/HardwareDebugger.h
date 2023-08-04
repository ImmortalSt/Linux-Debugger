#include "../DebuggerBase.h"
#include <functional>
#include <iostream>
#include <array>
#include <sys/user.h>


class HardwareDebugger : public DebuggerBase {
public:
    enum condition {
        EXEC = 0,
        WO = 1,
        PORT = 2,
        RW = 3
    };

    HardwareDebugger() : DebuggerBase(0) {}
    HardwareDebugger(uint64_t pid) : DebuggerBase(pid) {}
    ~HardwareDebugger();

    int SetBreakpoint(uint64_t address, uint8_t condition, uint16_t size, void (*observer)(struct user_regs_struct regs)) override;
    int DelBreakpoint(uint64_t address) override;
    void StartDebugLoop() override;

private:
    std::array<std::function<void(struct user_regs_struct)>, 4> _osbservers;
};
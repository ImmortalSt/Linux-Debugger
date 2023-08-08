#include "SoftwareDebugger.h"
#include <sys/ptrace.h>
#include <signal.h>

int SoftwareDebugger::SetBreakpoint(uint64_t address, uint8_t condition, uint16_t size, void(* observer)(user_regs_struct regs))
{
    if (condition != 1) {
        std::cout << "incorrect condition\n";
        return 1;
    }

    breakpoint bp {0};
    bp.oldByte = ReadByte(address);

    WriteByte(address, 0xCC);

    bp.address = address;
    bp.observer = observer;

    _breakpoints.push_back(bp);

    return 0;
}

int SoftwareDebugger::DelBreakpoint(uint64_t address) {
    for (auto& bp : _breakpoints) {
        if (bp.address == address) {
            WriteByte(bp.address, bp.oldByte);
        }
    }
    return 0;
}

void SoftwareDebugger::StartDebugLoop() {
    while(1) {

        auto a = WaitException();

        auto context = GetContext();

        for (auto& bp : _breakpoints) {
            if (bp.address == context.rip - 1) {
                WriteByte(bp.address, bp.oldByte);
                context.rip -= 1;
                SetContext(context);
                DoDebugStep();
                auto h = GetContext();
                WriteByte(bp.address, 0xCC);
                bp.observer(context);

                break;
            }
        }
    }
}

int SoftwareDebugger::WriteByte(uint64_t address, uint8_t byte) {
    Write<uint8_t>(address, byte);
    return 0;
}
uint8_t SoftwareDebugger::ReadByte(uint64_t address) {
    return Read<uint8_t>(address);
}

SoftwareDebugger::~SoftwareDebugger() {
    for (auto& bp : _breakpoints) {
        WriteByte(bp.address, bp.oldByte);
    }
}
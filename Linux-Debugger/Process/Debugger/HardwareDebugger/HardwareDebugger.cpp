#include "HardwareDebugger.h"

bool is_first = true;
int HardwareDebugger::SetBreakpoint(uint64_t address, uint8_t condition, uint16_t size, void(* observer)(user_regs_struct regs))
{
    if (is_first) {
        is_first = false;
        ClearBreakpoints();
    }

    if (condition > 3){
        std::cout << "incorrect condition\n";
        return 3;
    }
    if (size != 1 && size != 2 && size != 4 && size != 8) {
        std::cout << "incorrect bp size\n";
        return 1;
    }

    int Drx = -1;

    for (int i = 0; i < 4; i++) {
        if (!GetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * i))) {
            Drx = i;
            break;
        }
    }

    if(Drx == -1) {
        std::cout << "No space for bp\n";
        return 2;
    }

    uint8_t options = 255;

    if (size == 1) options = 0;
    else if (size == 2) options = 1;
    else if (size == 4) options = 3;
    else if (size == 8) options = 2;

    options = options << 2;

    options = options | condition;

    uint64_t Dr7 = GetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * 7));

    Dr7 |= (0b1 << (Drx * 2));

    Dr7 |= (options << (16 + (Drx * 4)));

    SetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * 7), Dr7);




    SetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * Drx), (long long)address);

    _breakpoints[Drx].observer = observer;
    _breakpoints[Drx].address = address;
    return 0;
}

int HardwareDebugger::DelBreakpoint(uint64_t address) {
    return 0;
}
void HardwareDebugger::StartDebugLoop() {
    while(1) {

        auto a = WaitException();
        uint64_t Dr6 = GetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * 6));
        
        if (Dr6 & 0b1111 && a == 1407) {
            for (int i = 0; i < 4; i++) {
                if (Dr6 & (0b1 << i)) {
                    _breakpoints[i].observer(GetContext());
                }
            }
            SetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * 6), Dr6 & ~(0b1111));
        }
    }
}


HardwareDebugger::~HardwareDebugger() {}
HardwareDebugger::HardwareDebugger(uint64_t pid) : DebuggerBase(pid) {
}

void HardwareDebugger::ClearBreakpoints() {
    SetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * 0), 0);
    SetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * 1), 0);
    SetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * 2), 0);
    SetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * 3), 0);
    SetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * 7), 0);
}

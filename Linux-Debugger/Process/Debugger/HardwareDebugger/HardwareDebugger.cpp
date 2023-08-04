#include "HardwareDebugger.h"



int HardwareDebugger::SetBreakpoint(uint64_t address, uint8_t condition, uint16_t size, void(* observer)(user_regs_struct regs))
{
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
        if (!_osbservers[i]) {
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

    long long Dr7 = GetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * 7));

    Dr7 |= options << (16 + (Drx * 4));
    Dr7 |= 0b1 << (Drx * 2);

    Dr7 &= ~0ull;

    SetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * 7), Dr7);

    SetRegister((x64userStructOffsets)(x64userStructOffsets::u_debugreg + sizeof(long long) * Drx), (long long)observer);

    _osbservers[Drx] = observer;
    return 0;
}

int HardwareDebugger::DelBreakpoint(uint64_t address) {
    return 0;
}
void HardwareDebugger::StartDebugLoop() {

}


HardwareDebugger::~HardwareDebugger() {}
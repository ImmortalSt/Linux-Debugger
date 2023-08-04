#include <cstdint>
#include <string>
#include <dirent.h>
#include "../../SmartDescriptor/SmartDescriptor.h"
#include <regex>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include "../Debugger/HardwareDebugger/HardwareDebugger.h"

typedef struct user_regs_struct context;
typedef struct user extended_context;

class Thread {
public:
    Thread(uint64_t pid);
    ~Thread();

    void EnableDebugging();
    void DisableDebugging();
    context GetContext();
    void SetRegister(x64userStructOffsets offset, long long value);
    long long int GetRegister(x64userStructOffsets offset);
    HardwareDebugger& GetHardwareDebugger();

private:
    bool _isDebugging = false;
    uint64_t _pid = 0;
    HardwareDebugger _hardwareDebugger;
};
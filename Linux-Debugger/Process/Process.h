#include <cstdint>
#include <cstdio>
#include <dirent.h>
#include "../SmartDescriptor/SmartDescriptor.h"
#include <fcntl.h>
#include <vector>
#include <cstring>
#include <string>
#include <regex>
#include "Module/Maps.h"
#include "Thread/ThreadList.h"

namespace dbg
{
    class Process {
    public:
        Maps maps;
        ThreadList threads;

        Process() {};
        Process(uint64_t pid);
        Process(const char* processName);
        ~Process();

        std::string ReadString(uint64_t address);
        template <typename T> T Read(uint64_t address) {
            return threads._threads[0].GetHardwareDebugger().Read<T>(address);
        }
        template <typename T> void Write(uint64_t address, T value) {
            threads._threads[0].GetHardwareDebugger().Write<T>(address, value);
        }
        
        uint64_t GetPid();
        void EnableDebugging();
        void DisableDebugging();
    private:
        void init(uint64_t pid);
        void initMaps();
        void initThreads();

        uint64_t _pid = 0;
        std::string _procPath;
    };

} 
#include <cstdint>
#include <cstdio>
#include <dirent.h>
#include "../SmartDescriptor/SmartDescriptor.h"
#include <fcntl.h>
#include <vector>
#include "Module/Module.h"
#include <cstring>
#include <string>
#include <regex>

namespace dbg
{
    class Process {
    public:
        Process(uint16_t pid);
        Process(char* processName);
        ~Process();

        template <typename T> T Read(uint64_t address) {
            T value = 0;
            SmartDescriptor<int> mem(open(_procPath.append("mem").c_str(), O_RDONLY));
            lseek64(mem, address, SEEK_SET);
            read(mem, &value, sizeof(value));
            return value;
        }

    private:
        void init(uint16_t pid);
        void initMaps();

        uint16_t _pid;
        std::string _procPath;
        
        std::vector<Module> _modules;
    };

} 
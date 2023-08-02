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

namespace dbg
{
    class Process {
    public:
        Maps maps;


        Process(uint64_t pid);
        Process(const char* processName);
        ~Process();

        template <typename T> T Read(uint64_t address) {
            T value = 0;
            std::string a = _procPath.append("mem");
            auto ad = fopen(a.c_str(), "rb");
            SmartDescriptor<FILE*> mem(fopen(a.c_str(), "rb"));
            fseek(mem, address, SEEK_SET);
            fread(&value, sizeof(T), 1, mem);
            return value;
        }

    private:
        void init(uint64_t pid);
        void initMaps();

        uint64_t _pid;
        std::string _procPath;
    };

} 
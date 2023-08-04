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

        Process(uint64_t pid);
        Process(const char* processName);
        ~Process();

        std::string ReadString(uint64_t address);
        template <typename T> T Read(uint64_t address) {
            T value = 0;
            SmartDescriptor<FILE*> mem(fopen((_procPath + "mem").c_str(), "rb"));
            fseek(mem, address, SEEK_SET);
            fread(&value, sizeof(T), 1, mem);
            return value;
        }
        template <typename T> void Write(uint64_t address, T value) {
            SmartDescriptor<FILE*> mem(fopen((_procPath + "mem").c_str(), "wb"));
            fseek(mem, address, SEEK_SET);
            fwrite(&value, sizeof(T), 1, mem);
        }
        
        uint64_t GetPid();
        void EnableDebugging();
        void DisableDebugging();
    private:
        void init(uint64_t pid);
        void initMaps();
        void initThreads();

        uint64_t _pid;
        std::string _procPath;
    };

} 
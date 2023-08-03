#include "Process.h"

dbg::Process::Process(uint64_t _pid)
{
    init(_pid);
}

bool is_number(char *str)
{
    char *endptr;
    std::strtol(str, &endptr, 10);

    return (*str != '\0' && *endptr == '\0');
}

dbg::Process::Process(const char *processName)
{
    SmartDescriptor<DIR*> procDir(opendir("/proc/"));

    dirent *entry;
    while ((entry = readdir(procDir)) != nullptr)
    {
        char *endptr = 0;
        if (is_number(entry->d_name))
        {
            std::string path = "/proc/";
            path += entry->d_name;
            path += "/cmdline";
            SmartDescriptor<int> cmdline(open(path.c_str(), O_RDONLY));
            char buffer[255];
            read(cmdline, buffer, 255);
            if (strcmp(buffer, processName) == 0)
            {
                init(std::stoi(entry->d_name));
                break;
            }
        }
    }

}

dbg::Process::~Process() {}

void dbg::Process::init(uint64_t pid)
{
    _pid = pid;
    _procPath = "/proc/" + std::to_string(pid) + "/";
    initMaps();
    initThreads();
}

void dbg::Process::initMaps()
{
    maps = Maps(_pid);
}
void dbg::Process::initThreads(){
    threads = ThreadList(_pid);
}

std::string dbg::Process::ReadString(uint64_t address){
    std::string res = "";
    char _c = 0;
    for (int i = 0; _c = Read<char>(address + i), _c != 0; i++) {
        res += _c;
    }
    return res;
}

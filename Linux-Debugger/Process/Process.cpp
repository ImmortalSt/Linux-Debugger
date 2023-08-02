#include "Process.h"

dbg::Process::Process(uint16_t _pid)
{
    init(_pid);
}

bool is_number(char *str)
{
    char *endptr;
    std::strtol(str, &endptr, 10);

    return (*str != '\0' && *endptr == '\0');
}

dbg::Process::Process(char *processName)
{
    DIR *procDir = opendir("/proc/");

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

void dbg::Process::init(uint16_t pid)
{
    _pid = pid;
    _procPath = "/proc/" + std::to_string(pid) + "/";
    initMaps();
}

void dbg::Process::initMaps()
{
    SmartDescriptor<std::ifstream> infile(std::ifstream(_procPath.append("maps").c_str()));

    std::string line;
    _modules.reserve(20);
    std::regex maps_pattern("(\\w+)-(\\w+) ([rwxp-]{4}) (\\w+) (\\w+):(\\w+) (\\w+)[ ]+([A-Za-z\\/\\[\\]\\-.0-9]+|)");
    std::smatch match_results;

    while (std::getline((std::ifstream &)infile, line))
    {
        //std::cout << line << std::endl;
        std::regex_search(line, match_results, maps_pattern);
        char* end;
        _modules.push_back(Module{
            std::strtoull(match_results[1].str().c_str(), &end, 16),
            std::strtoull(match_results[2].str().c_str(), &end, 16),
            std::move(match_results[3].str()),
            std::strtoull(match_results[4].str().c_str(), &end, 16),
            static_cast<uint16_t>(std::stoi(match_results[5].str().c_str(), nullptr, 10)),
            static_cast<uint16_t>(std::stoi(match_results[6].str().c_str(), nullptr, 10)),
            std::strtoull(match_results[7].str().c_str(), &end, 16),
            std::move(match_results[8].str())
        });
    }
        int a = 0;
}

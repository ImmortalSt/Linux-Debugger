#include "Maps.h"

Maps::Maps() {}
Maps::Maps(uint64_t pid) {
    std::string a = "/proc/" + std::to_string(pid) + "/maps";
    SmartDescriptor<std::ifstream> infile(std::ifstream("/proc/" + std::to_string(pid) + "/maps"));
    perror("ddd");
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

}

uint64_t Maps::GetBaseAddress() {
    return _modules[0].startAddress;
}

Maps::~Maps() {}
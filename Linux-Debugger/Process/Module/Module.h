#include <cstdint>
#include <string>

class Module {
public:
    uint64_t startAddress = 0;
    uint64_t endAddress = 0;
    std::string mode;
    uint64_t offset = 0;
    uint16_t majorId = 0;
    uint16_t minorId = 0;
    uint64_t inodeId = 0;
    std::string filePath;
};
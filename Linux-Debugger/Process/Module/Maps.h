#include <vector>
#include "Module.h"
#include "../../SmartDescriptor/SmartDescriptor.h"
#include <string>
#include <regex>

class Maps
{
private:
    std::vector<Module> _modules;
public:
    uint64_t GetBaseAddress();

    Maps();
    Maps(uint64_t pid);
    ~Maps();
};

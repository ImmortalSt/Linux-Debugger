#include <cstdint>
#include <string>
#include <dirent.h>
#include "../../SmartDescriptor/SmartDescriptor.h"

class Thread {
public:
    Thread();
    Thread(char* path);
    ~Thread();
private:
    uint64_t _threadId = 0;
};
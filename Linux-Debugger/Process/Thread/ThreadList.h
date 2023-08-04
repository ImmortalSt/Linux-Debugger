#include <vector>
#include <cstdint>
#include "Thread.h"
#include <string>

class ThreadList {
public:
    ThreadList();
    ThreadList(uint64_t pid);
    ~ThreadList();
private:
    std::vector<Thread> _threads;
    
};

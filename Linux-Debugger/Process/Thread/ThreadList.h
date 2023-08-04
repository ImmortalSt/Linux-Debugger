#include <vector>
#include <cstdint>
#include "Thread.h"
#include <string>

class ThreadList {
public:
    ThreadList();
    ThreadList(uint64_t pid);
    ~ThreadList();
    std::vector<Thread> _threads;
private:
    
};

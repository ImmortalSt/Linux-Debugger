#include "Thread.h"

Thread::Thread() {};
Thread::Thread(char* path) {
    std::cout << path << '\n';
}

Thread::~Thread() {}
#include "ThreadList.h"

bool is_number_str(char* str)
{
    char *endptr;
    std::strtol(str, &endptr, 10);

    return (*str != '\0' && *endptr == '\0');
}

ThreadList::ThreadList() {}
ThreadList::ThreadList(uint64_t pid) {
    std::string threadsPath = "/proc/" + std::to_string(pid) + "/task/";
    SmartDescriptor<DIR*> threadsDir(opendir(threadsPath.c_str()));
    dirent *entry;
    while ((entry = readdir(threadsDir)) != nullptr)
    {
        if (is_number_str(entry->d_name)) {

            _threads.push_back(Thread((char*)(threadsPath + entry->d_name).c_str()));
        }
    }
}

ThreadList::~ThreadList() {}
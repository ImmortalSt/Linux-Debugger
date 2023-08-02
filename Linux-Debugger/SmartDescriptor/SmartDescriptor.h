#ifndef _SMARTDESCRIPTOR_
#define _SMARTDESCRIPTOR_

#include <type_traits>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <type_traits>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

template<typename T>
class SmartDescriptor {
public:
    SmartDescriptor(T&& descriptor) noexcept : _descriptor(std::forward<T>(descriptor)) {}

    ~SmartDescriptor() noexcept {
        if constexpr (has_close::value) {
            _descriptor.close();
        } else {
            if (fd_is_valid(_descriptor)) {
                close(_descriptor);
            }
        }
    }

    operator T&() {
        return _descriptor;
    }
private:
    T _descriptor;
    
    struct has_close
    {
        private:
            typedef char yes;
            typedef struct { yes dummy[2]; } no;

            template<typename U>
            static auto check(U* u) -> decltype((*u).close(), yes());
            
            static no check(...);
        public:
        enum {
            value = (sizeof(check((T*)0)) == sizeof(yes))
        };

    };
    

    int fd_is_valid(int fd)
    {
        return fcntl(fd, F_GETFD) != -1;
    }
};


#endif
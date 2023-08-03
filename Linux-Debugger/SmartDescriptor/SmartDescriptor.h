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
        if constexpr (sizeof(des_close((T*)0)) == sizeof(external_fclose)) {
            if (_descriptor != 0)
                fclose(_descriptor);
        }
        if constexpr (sizeof(des_close((T*)0)) == sizeof(external_close)) {
            if(_descriptor != -1)
                close(_descriptor);
        }
        if constexpr (sizeof(des_close((T*)0)) == sizeof(internal_close)) {
            _descriptor.close();
        }
        if constexpr (sizeof(des_close((T*)0)) == sizeof(external_closedir)) {
            closedir(_descriptor);
        }

    }

    operator T&() {
        return _descriptor;
    }
private:
    T _descriptor;

    typedef struct { char a; } external_fclose;
    typedef struct { char a[2]; } external_close;
    typedef struct { char a[3]; } internal_close;
    typedef struct { char a[4]; } external_closedir;

    template<typename U>
    static auto  des_close(U* u) -> decltype(fclose(*u), external_fclose());
    template<typename U>
    static auto  des_close(U* u) -> decltype(close(*u), external_close());
    template<typename U>
    static auto  des_close(U* u) -> decltype((*u).close(), internal_close());
    template<typename U>
    static auto  des_close(U* u) -> decltype(closedir(*u), external_closedir());


    int fd_is_valid(int fd)
    {
        return fcntl(fd, F_GETFD) != -1;
    }
};


#endif
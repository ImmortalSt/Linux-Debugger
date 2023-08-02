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

        des_close(std::move(_descriptor));

        //if constexpr (std::is_same<decltype(T::close), void>::value) {
        //    _descriptor.close();
        //} else if(std::is_same<T, int>::value) {
        //    if (fd_is_valid(_descriptor)) {
        //        close(_descriptor);
        //    }
        //} else if (std::is_same<T, _IO_FILE*>::value) {
        //    fclose(_descriptor);
        //} else {
//
        //}
    }

    operator T&() {
        return _descriptor;
    }
private:
    T _descriptor;

    void des_close(_IO_FILE* u) {
        fclose(_descriptor);
    }

    void des_close(int u) {
        close(_descriptor);
    }

    void des_close(...) {
        _descriptor.close();
    }

    int fd_is_valid(int fd)
    {
        return fcntl(fd, F_GETFD) != -1;
    }
};


#endif
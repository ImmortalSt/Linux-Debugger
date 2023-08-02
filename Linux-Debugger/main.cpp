#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "Process/Process.h"
#include "SmartDescriptor/SmartDescriptor.h"


int main() {
    dbg::Process proc("./a.out");
    auto a = proc.Read<char>(0x0);
    int b  = 0;
} 
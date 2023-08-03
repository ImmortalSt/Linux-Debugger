#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "Process/Process.h"
#include "SmartDescriptor/SmartDescriptor.h"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>

int main() {
    dbg::Process proc("./a.out");
    struct user_regs_struct regs;
    int b  = 0;
} 
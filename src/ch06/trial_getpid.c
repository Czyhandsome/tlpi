//
// Created by 曹子钰 on 2019/10/7.
//
#include "tlpi_hdr.h"
#include <unistd.h>

int main() {
    int pid = getpid();
    int ppid = getppid();

    printf("[PID]: %d\n[PPID]: %d\n", pid, ppid);
    return 0;
}
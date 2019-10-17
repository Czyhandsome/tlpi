//
// Created by 曹子钰 on 2019/10/16.
//
#include "unistd.h"
#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
    printf("uid: %d\n", getuid());
    printf("gid: %d\n", getgid());
    printf("effective uid: %d\n", geteuid());
    printf("effective gid: %d\n", getegid());

    if (setuid(12) != 0) {
        errExit("setuid");
    }

    if (setgid(16) != 0) {
        errExit("setgid");
    }

    printf("changed: uid: %d\n", getuid());
    printf("changed: gid: %d\n", getgid());
    printf("changed: effective uid: %d\n", geteuid());
    printf("changed: effective gid: %d\n", getegid());

    return 0;
}
//
// Created by 曹子钰 on 2019/10/16.
//

#include <unistd.h>
#include <tlpi_hdr.h>

void printIds(const char *prefix) {
    printf("%s uid: %d\n", prefix, getuid());
    printf("%s gid: %d\n", prefix, getgid());
    printf("%s effective uid: %d\n", prefix, geteuid());
    printf("%s effective gid: %d\n", prefix, getegid());
}

int main(int argc, char *argv[]) {
    printIds("Before");

    uid_t uid = getuid();
    gid_t gid = getgid();

    if (seteuid(uid) != 0) {
        errExit("seteuid");
    }

    if (setegid(gid) != 0) {
        errExit("setegid");
    }

    printIds("After set");

    uid_t euid = geteuid();
    gid_t guid = getegid();

    if (seteuid(euid) != 0) {
        errExit("seteuid");
    }

    if (setegid(guid) != 0) {
        errExit("setegid");
    }

    printIds("After set e");
}
//
// Created by 曹子钰 on 2019/10/7.
//

#include <stdlib.h>
#include "tlpi_hdr.h"

int main(int argc, char **argv) {
    printf("%s\n", getenv("PATH"));

    if (putenv("PATH=abc") != 0) {
        errExit("putenv");
    }
    printf("%s\n", getenv("PATH"));

    // Error: NO "="
    if (putenv("PATH") != 0) {
        errExit("putenv");
    }
    printf("%s\n", getenv("PATH"));

    return 0;
}
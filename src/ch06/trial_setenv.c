//
// Created by 曹子钰 on 2019/10/7.
//

#include "stdlib.h"
#include "tlpi_hdr.h"

int main() {
    char *path = "PATH";
    printf("PATH: %s\n", getenv(path));

    char value[] = "abc";

    if (setenv(path, value, 0) < 0) {
        errExit("setenv");
    }
    printf("PATH: %s\n", getenv(path));

    if (setenv(path, value, 1) < 0) {
        errExit("setenv");
    }
    printf("PATH: %s\n", getenv(path));

    value[1] = 'p';
    printf("After change: PATH: %s\n", getenv(path));

    return 0;
}
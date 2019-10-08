//
// Created by 曹子钰 on 2019/10/7.
//

#include "stdlib.h"
#include "tlpi_hdr.h"

int main() {
    const char *path = "PATH";
    printf("PATH: %s\n", getenv(path));

    unsetenv(path);
    printf("PATH: %s\n", getenv(path));

    if (unsetenv("ABC") == -1) {
        errExit("unsetenv");
    } else {
        printf("unsetenv success.");
    }

    return 0;
}
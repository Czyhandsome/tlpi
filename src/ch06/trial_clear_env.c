//
// Created by 曹子钰 on 2019/10/7.
//
#define _BSD_SOURCE

#include "tlpi_hdr.h"
#include "stdlib.h"

extern char *environ;

int main() {
    printf("%s\n", getenv("PATH"));

    char *old = environ;
    environ = NULL;

    printf("old_environ: %p\n", old);
    printf("%s\n", getenv("PATH"));

    environ = old;
    printf("%s\n", getenv("PATH"));

    return 0;
}
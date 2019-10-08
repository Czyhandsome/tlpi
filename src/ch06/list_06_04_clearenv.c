//
// Created by 曹子钰 on 2019/10/7.
//

#include "stdlib.h"
#include "tlpi_hdr.h"

extern char **environ;

int main(int argc, char *argv[]) {
    environ = NULL;

    if (setenv("GREET", "Hello World", 0) == -1) {
        errExit("setenv");
    }

    int i;
    for (i = 1; i < argc; ++i) {
        if (putenv(argv[i]) != 0) {
            errExit("putenv: %s", argv[i]);
        }
    }

    unsetenv("BYE");

    char **ep;
    for (ep = environ; *ep != NULL; ++ep) {
        puts(*ep);
    }

    return 0;
}
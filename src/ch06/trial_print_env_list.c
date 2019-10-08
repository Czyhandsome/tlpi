//
// Created by 曹子钰 on 2019/10/7.
//

#include "tlpi_hdr.h"

extern char **environ;

int main() {
    char **p;
    for (p = environ; p != NULL; ++p) {
        printf("%s\n", *p);
    }
    
    return 0;
}
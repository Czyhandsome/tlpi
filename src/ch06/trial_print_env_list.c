//
// Created by 曹子钰 on 2019/10/7.
//

#include "tlpi_hdr.h"

extern char **environ;

int main() {
    for (char **p = environ; p != NULL; ++p) {
        printf("%s\n", *p);
    }
    
    return 0;
}
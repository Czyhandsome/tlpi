//
// Created by 曹子钰 on 2019/10/7.
//
#include "tlpi_hdr.h"

int main(int argc, char **argv, char **envp) {
    char **p;
    for (p = envp; p != NULL; ++p) {
        puts(*p);
    }
    
    return 0;
}
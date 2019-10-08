//
// Created by 曹子钰 on 2019/10/7.
//

#include <zconf.h>
#include "tlpi_hdr.h"

int main() {
    printf("%ld\n", sysconf(_SC_ARG_MAX));
}
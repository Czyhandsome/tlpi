//
// Created by 曹子钰 on 2019/10/7.
//

#include <zconf.h>
#include "tlpi_hdr.h"

int main() {
    long page_size = sysconf(_SC_PAGE_SIZE);
    if (page_size < 0) {
        errExit("sysconf");
    }
    printf("%ld\n", page_size);
}
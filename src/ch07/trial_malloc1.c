//
// Created by 曹子钰 on 2019/10/8.
//
#include "stdlib.h"
#include "unistd.h"
#include "tlpi_hdr.h"

int main() {
    // Print origin heap
    printf("before malloc: %p\n", sbrk(0));

    // malloc
    void *ml = malloc(100 * 1024 * 1024);
    if (ml == NULL) {
        errExit("malloc");
    }

    printf("after malloc: %p\n", sbrk(0));

    // free
    free(ml);
    printf("after free: %p\n", sbrk(0));

    return 0;
}
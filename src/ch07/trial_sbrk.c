//
// Created by 曹子钰 on 2019/10/8.
//

#include <unistd.h>
#include "tlpi_hdr.h"

int main() {
    void *heap = sbrk(0);
    printf("%p", heap);

    return 0;
}
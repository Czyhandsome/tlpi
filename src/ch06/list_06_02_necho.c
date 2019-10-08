//
// Created by 曹子钰 on 2019/10/7.
//

#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return 0;
}
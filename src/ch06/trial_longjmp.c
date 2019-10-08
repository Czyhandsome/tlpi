//
// Created by 曹子钰 on 2019/10/7.
//

#include "setjmp.h"
#include "tlpi_hdr.h"

static jmp_buf env;

int main(int argc, char *argv[]) {
    switch (setjmp(env)) {
        case 1:
            printf("1");
            return 0;
        case 2:
            printf("2");
            return 0;
    }

    if (argc == 1) {
        longjmp(env, 1);
    } else {
        longjmp(env, 2);
    }
}
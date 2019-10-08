//
// Created by 曹子钰 on 2019/10/7.
//
#include <setjmp.h>
#include "tlpi_hdr.h"

static jmp_buf env;

static void f2() {
    longjmp(env, 2);
}

static void f1(int argc) {
    if (argc == 1) {
        longjmp(env, 1);
    }
    f2();
}

int main(int argc, char *argv[]) {
    switch (setjmp(env)) {
        /* This is the return after the initial setjmp() */
        case 0:
            printf("Calling f1() after initial setjmp()\n");
            /* Never returns... */
            f1(argc);
            /* ... but this is good form */
            break;
        case 1:
            printf("We jumped back from f1()\n");
            break;
        case 2:
            printf("We jumped back from f2()\n");
            break;
    }

    return 0;
}
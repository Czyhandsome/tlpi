//
// Created by 曹子钰 on 2019/10/7.
//

#include "setjmp.h"
#include "tlpi_hdr.h"

static jmp_buf env;

static void shoot() {
    setjmp(env);
}

int main(int argc, char *argv[]) {
    shoot();
    longjmp(env, 2);

    return 0;
}
//
// Created by 曹子钰 on 2019/10/28.
//

#include "sys/time.h"
#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
    struct timeval t;
    t.tv_sec = 1000;

    int res = gettimeofday(&t, NULL);
    if (res < 0) {
        errExit("gettimeofday");
    }

    printf("Sec: %ld, Usec: %d", t.tv_sec, t.tv_usec);

    return 0;
}
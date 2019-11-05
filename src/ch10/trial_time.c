//
// Created by 曹子钰 on 2019/10/29.
//
#include "time.h"
#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
    int t = time(NULL);
    printf("UNIX time seconds: %d\n", t);

    return 0;
}
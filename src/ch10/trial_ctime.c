//
// Created by 曹子钰 on 2019/10/29.
//
#include <sys/time.h>
#include <time.h>
#include <tlpi_hdr.h>

int main(int argc, char *argv[]) {
    struct timeval tv;
    int res = gettimeofday(&tv, NULL);

    struct ttinfo {
        long t1;
        int t2;
        unsigned int t3;
    };

    printf("%ld", sizeof(struct ttinfo));
}
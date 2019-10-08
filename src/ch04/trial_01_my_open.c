//
// Created by 曹子钰 on 2019/10/5.
//
#include "tlpi_hdr.h"
#include <fcntl.h>

int main() {
    const char *path = "/Users/caoziyu/CLionProjects/linux/src/ch04/my_open.c";

    int fd = open(path, O_RDWR);
    if (fd == -1) {
        errExit("open");
    }

    // Allocate buffer
#define BUF_SIZE 512
    char buf[BUF_SIZE];

    int rd;
    while ((rd = read(fd, buf, BUF_SIZE) != 0)) {
        if (rd == -1) {
            errExit("read");
            break;
        }

        printf("length: %d\n", rd);
        printf("%s", buf);
    }

    if (close(fd) == -1) {
        errExit("close");
    }
}
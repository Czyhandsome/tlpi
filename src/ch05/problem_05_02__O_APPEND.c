//
// Created by 曹子钰 on 2019/10/6.
//

#include <fcntl.h>
#include <error_functions.h>
#include <zconf.h>
#include "tlpi_hdr.h"

int main() {
    int fd = open("sl.txt", O_APPEND | O_WRONLY);
    if (fd == -1) {
        errExit("open");
    }

    lseek(fd, 0, SEEK_SET);
    if (write(fd, "hello", strlen("hello")) == -1) {
        errExit("write");
    }

    if (close(fd) == -1) {
        errExit("close");
    }

    return 0;
}
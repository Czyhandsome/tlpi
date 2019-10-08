//
// Created by 曹子钰 on 2019/10/5.
//
#include "tlpi_hdr.h"
#include <fcntl.h>

int main() {

#define BUF_SIZE 20
    char buf[BUF_SIZE + 1];

    int rd = read(STDIN_FILENO, buf, BUF_SIZE);
    if (rd == -1) {
        errExit("read");
    }

    // Manually add '\0' to end of buf
    buf[BUF_SIZE] = '\0';
    printf("The input data was: %s\n", buf);
}
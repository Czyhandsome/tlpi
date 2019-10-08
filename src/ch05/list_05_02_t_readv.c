//
// Created by 曹子钰 on 2019/10/6.
//
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main() {
    int fd;
    struct iovec iov[3];
    /* First buffer */
    struct stat st;
    /* Second buffer */
    int x;

#define STR_SIZE 100
    /* Third buffer */
    char str[STR_SIZE];
    ssize_t numRead, totRequired;

    fd = open("aa.txt", O_RDONLY);
    if (fd == -1) {
        errExit("open");
    }

    totRequired = 0;

    iov[0].iov_base = &st;
    iov[0].iov_len = sizeof(struct stat);
    totRequired += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    totRequired += iov[1].iov_len;

    iov[2].iov_base = str;
    iov[2].iov_len = sizeof(char) * STR_SIZE;
    totRequired += iov[2].iov_len;

    numRead = readv(fd, iov, 3);
    if (numRead == -1) {
        errExit("readv");
    }

    if (numRead < totRequired) {
        printf("Read fewer bytes than required\n");
    }

    printf("total bytes requested: %ld; bytes read: %ld\n",
           (long) totRequired, (long) numRead);

    printf("st.st_mode: %ld, st.st_dev: %ld\n", (long) st.st_mode, (long) st.st_dev);
    printf("x: %d\n", x);
    printf("str: %s\n", str);
    return 0;
}
//
// Created by 曹子钰 on 2019/10/6.
//
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main() {
    // Data to write
    struct iovec iov[3];

    // read file from CMakeLists.txt
    int fd = open("CMakeLists.txt", O_RDONLY);
    if (fd == -1) {
        errExit("open");
    }
    // Get stats
    struct stat st;
    int res = fstat(fd, &st);
    if (res == -1) {
        errExit("fstat");
    }

    if (close(fd) == -1) {
        errExit("close");
    }

    // Setup iov[0]
    iov[0].iov_base = &st;
    iov[0].iov_len = sizeof(st);

    // Setup iov[1]
    int x = 5;
    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);

    // Setup iov[2]
#define STR_SIZE 100
    char str[100];
    const char *template = "abc";
    int i;
    for (i = 0; i < 99; ++i) {
        str[i] = template[i % 3];
    }
    str[99] = '\0';
    iov[2].iov_base = str;
    iov[2].iov_len = sizeof(char) * 100;

    // Expected number of bytes to read
    ssize_t expectedNumWrite = iov[0].iov_len + iov[1].iov_len + iov[2].iov_len;

    // Do write
    fd = open("aa.txt", O_RDWR | O_CREAT | O_TRUNC, 0640);
    if (fd == -1) {
        errExit("open 2");
    }
    ssize_t numWrite = writev(fd, iov, 3);
    if (numWrite == -1) {
        errExit("write");
    }

    if (numWrite != expectedNumWrite) {
        printf("expected: %ld, actual: %ld", expectedNumWrite, numWrite);
    }
    printf("Done write");
}
//
// Created by 曹子钰 on 2019/10/7.
//
#include "tlpi_hdr.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if ((argc < 3 || argc > 4) || strcmp(argv[1], "--help") == 0) {
        usageErr("%s filename num-bytes [x]\n", argv[0]);
    }

    const char *filename = argv[1];
    size_t num_bytes = getLong(argv[2], GN_ANY_BASE, argv[2]);

    if (argc == 3) {
        void atomic_append(const char *filename, size_t num_bytes);
        atomic_append(filename, num_bytes);
    } else {
        void non_atomic_append(const char *filename, size_t num_bytes);
        non_atomic_append(filename, num_bytes);
    }

    return 0;
}

void atomic_append(const char *filename, size_t num_bytes) {
    int fd = open(filename, O_WRONLY | O_APPEND);
    if (fd == -1) {
        errExit("open");
    }

    /* Prepare the data */
    char data[num_bytes];
    for (size_t i = 0; i < num_bytes; ++i) {
        data[i] = '\0';
    }

    /* Write data */
    ssize_t wt = write(fd, data, num_bytes);
    if (wt == -1) {
        errExit("write");
    }
    if (wt != num_bytes) {
        fatal("expected wt: %ld, actual: %ld", wt, num_bytes);
    }

    if (close(fd) == -1) {
        errExit("close");
    }
}

void non_atomic_append(const char *filename, size_t num_bytes) {
    int fd = open(filename, O_WRONLY | O_APPEND);
    if (fd == -1) {
        errExit("open");
    }

    /* seek */
    int sk = lseek(fd, 0, SEEK_END);
    if (sk < 0) {
        errExit("lseek");
    }

    /* Prepare the data */
    char data[num_bytes];
    for (size_t i = 0; i < num_bytes; ++i) {
        data[i] = '\0';
    }

    /* Write data */
    ssize_t wt = write(fd, data, num_bytes);
    if (wt == -1) {
        errExit("write");
    }
    if (wt != num_bytes) {
        fatal("expected wt: %ld, actual: %ld", wt, num_bytes);
    }

    if (close(fd) == -1) {
        errExit("close");
    }
}
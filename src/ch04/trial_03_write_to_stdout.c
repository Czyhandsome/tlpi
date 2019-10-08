//
// Created by 曹子钰 on 2019/10/5.
//
#include <fcntl.h>
#include "tlpi_hdr.h"

int main() {
    char data[] = "abc12345";

    int fd = open("write_to_stdout.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        errExit("open");
    }

    ssize_t wt = write(fd, data, sizeof(data));
    if (wt == -1) {
        errExit("write");
    }

    printf("number bytes write: %ld\n", (long) wt);

    if (close(fd) == -1) {
        errExit("close");
    }
}

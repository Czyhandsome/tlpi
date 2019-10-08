//
// Created by 曹子钰 on 2019/10/5.
//
#include "tlpi_hdr.h"
#include "fcntl.h"

int main() {
    int fd = open("write_file_hole.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        errExit("open");
    }

    const char *data = "hello dear all!";
    size_t nBytes = strlen(data) + 1;
    ssize_t wt = write(fd, data, nBytes);
    if (wt == -1) {
        errExit("write first");
    }

    off_t offset = lseek(fd, 1000, SEEK_END);
    if (offset == -1) {
        errExit("lseek");
    }

    wt = write(fd, data, nBytes);
    if (wt == -1) {
        errExit("write second");
    }

    if (close(fd) == -1) {
        errExit("close");
    }
}
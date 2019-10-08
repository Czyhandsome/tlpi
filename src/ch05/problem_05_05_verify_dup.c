//
// Created by 曹子钰 on 2019/10/7.
//

#include <fcntl.h>
#include <tlpi_hdr.h>
#include <sys/stat.h>

int main() {
    // Open CMakeLists.txt
    int fd = open("CMakeLists.txt", O_RDONLY);
    if (fd < 0) {
        errExit("open");
    }

    int fdd = dup(fd);
    if (fdd < 0) {
        errExit("dup");
    }

    // Check flag equality
    int flags = fcntl(fd, F_GETFL);
    if (flags < 0) {
        errExit("fcntl");
    }
    int flags_d = fcntl(fdd, F_GETFL);
    if (flags_d < 0) {
        errExit("fcntl");
    }
    printf("origin: before flags: %d, dup flags: %d\n", flags, flags_d);

    // Change flag
    if (fcntl(fd, F_SETFL, flags | O_ASYNC) < 0) {
        errExit("fcntl");
    }
    flags = fcntl(fd, F_GETFL);
    if (flags < 0) {
        errExit("fcntl");
    }
    flags_d = fcntl(fdd, F_GETFL);
    if (flags_d < 0) {
        errExit("fcntl");
    }
    printf("after SETFL: before flags: %d, dup flags: %d\n", flags, flags_d);

    // Origin offset
    off_t offset = lseek(fd, 0, SEEK_CUR);
    off_t offset_d = lseek(fdd, 0, SEEK_CUR);
    printf("origin: before offset: %ld, dup offset: %ld\n", (long) offset, (long) offset_d);

    // lseek to other offset
    offset_d = lseek(fdd, -100, SEEK_END);
    offset = lseek(fd, 0, SEEK_CUR);
    printf("after lseek: before offset: %ld, dup offset: %ld\n", (long) offset, (long) offset_d);
}
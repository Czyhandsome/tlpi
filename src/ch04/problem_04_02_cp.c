//
// Created by 曹子钰 on 2019/10/6.
//
#include "tlpi_hdr.h"
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 3 || (argc > 1 && strcmp(argv[1], "--help") == 0)) {
        usageErr("Usage: %s [src] [dest]\n", argv[0]);
    }

    const char *src = argv[1];
    const char *dest = argv[2];

    int fdSrc = open(src, O_RDONLY);
    if (fdSrc == -1) {
        errExit("open src");
    }
    struct stat statSrc;
    int st = fstat(fdSrc, &statSrc);
    if (st == -1) {
        errExit("get src stat");
    }
    mode_t perm = statSrc.st_mode & 0777;
    printf("Source stat: %o\n", perm);
    printf("%d\n", 0600 == perm);

    int fdDst = open(dest, O_WRONLY | O_TRUNC | O_CREAT, /*S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH*/
                     perm);
    if (fdDst == -1) {
        errExit("open dst");
    }

    ssize_t rd;
#define BUF_SIZE 512
    char data[BUF_SIZE];
    while ((rd = read(fdSrc, data, BUF_SIZE)) != 0) {
        if (rd == -1) {
            errExit("read from src");
        }
        // Test if all bytes read are zeros
        Boolean allZero = TRUE;
        for (ssize_t i = 0; i < rd; ++i) {
            if (data[i] != 0) {
                allZero = FALSE;
                break;
            }
        }
        // If all zero, make hole instead of write
        if (allZero) {
            int sk = lseek(fdDst, rd, SEEK_END);
            if (sk == -1) {
                errExit("lseek %s [%d]bytes", dest, rd);
            }
        }
            // If not all zero, do write
        else {
            ssize_t wt = write(fdDst, data, rd);
            if (wt == -1) {
                errExit("write to src");
            }
            if (wt != rd) {
                fatal("write to dst: expected length %ld, actual %ld", rd, wt);
            }
        }
    }

    if (close(fdSrc) == -1) {
        errExit("close src");
    }
    if (close(fdDst) == -1) {
        errExit("close dst");
    }

    return 0;
}
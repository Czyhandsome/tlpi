//
// Created by 曹子钰 on 2019/10/6.
//
#include "tlpi_hdr.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {
    const char *filename = "xy.txt";
    int fd = open(filename, O_WRONLY);
    if (fd != -1) {
        printf("[PID %ld] File \"%s\" already exists\n", (long) getpid(), filename);
        close(fd);
    } else {
        /* Failed for unexpected reason */
        if (errno != ENOENT) {
            errExit("open");
        } else {
            // Window for failure
            printf("[PID %ld] File \"%s\" doesn't exist yet\n", (long) getpid(), filename);
            if (argc > 1) {
                sleep(5);
                printf("[PID %ld] Done sleeping\n", (long) getpid());
            }
            fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
            if (fd == -1) {
                errExit("open");
            }

            printf("[PID %ld] Create file \"%s\" exclusively\n", (long) getpid(), filename);
        }
    }

    return 0;
}
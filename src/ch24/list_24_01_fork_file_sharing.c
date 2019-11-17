//
// Created by 曹子钰 on 2019/11/17.
//
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "tlpi_hdr.h"

void printInfo(int fd);

int main(int argc, char *argv[]) {
    int fd, flags;
    char template[] = "/tmp/testXXXXXX";

    // Disable buffering of stdout
    setbuf(stdout, NULL);

    fd = mkstemp(template);
    if (fd == -1) {
        errExit("mkstemp");
    }


    printInfo(fd);

    switch (fork()) {
        case -1:
            errExit("fork");
            break;

        case 0:
            if (lseek(fd, 1000, SEEK_CUR) == -1) {
                errExit("lseek");
            }
            flags = fcntl(fd, F_GETFL);
            if (flags == -1) {
                errExit("fcntl - F_GETFL");
            }
            flags |= O_APPEND;
            if (fcntl(fd, F_SETFL, flags) == -1) {
                errExit("fcntl - F_SETFL");
            }
            _exit(EXIT_SUCCESS);

        default:
            if (wait(NULL) < 0) {
                errExit("wait");
            }
            printf("Child has exited\n");

            printInfo(fd);

            exit(EXIT_SUCCESS);
    }
}

void printInfo(int fd) {
    int flags;
    printf("File offset before fork: %lld\n",
           (long long) lseek(fd, 0, SEEK_CUR));

    flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        errExit("fcntl - F_GETFL");
    }

    printf("O_APPEND flag before fork() is: %s\n",
           (flags & O_APPEND) ? "on" : "off");
}

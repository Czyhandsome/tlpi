//
// Created by 曹子钰 on 2019/11/17.
//

#include "unistd.h"
#include "tlpi_hdr.h"

// Allocated in data segment
static int idata = 111;

int main(int argc, char *argv[]) {
    // Allocated in stack segment
    int istack = 222;
    pid_t childPid;

    switch (childPid = fork()) {
        // Error
        case -1:
            errExit("fork");

            // Child
        case 0:
            idata *= 3;
            istack *= 3;
            break;

            // Parent
        default:
            sleep(1);
            break;
    }

    // Both parent and child come here.
    printf("PID=%ld PPID=%ld %s idata=%d istack=%d\n", (long) getpid(), (long) getppid(),
           (childPid == 0) ? "(child)" : "(parent)", idata, istack);

    exit(EXIT_SUCCESS);
}
//
// Created by 曹子钰 on 2020/5/23.
//

#include "read_line.h"
#include <unistd.h>
#include <errno.h>

ssize_t read_line(int fd, void *buffer, size_t n) {
    ssize_t numRead;
    size_t totalRead;
    char *buf;
    char ch;

    if (n <= 0 || buffer == NULL) {
        errno = EINVAL;
        return -1;
    }

    buf = buffer;

    totalRead = 0;
    for (;;) {
        numRead = read(fd, &ch, 1);
        if (numRead == -1) {
            /* Interrupted: Retry */
            if (errno == EINTR) {
                continue;
            } else {
                return -1;
            }
        } else if (numRead == 0) {
            if (totalRead == 0) {
                return 0;
            } else {
                break;
            }
        } else {
            if (totalRead < n - 1) {
                ++totalRead;
                *buf++ = ch;
            }

            if (ch == '\n') {
                break;
            }
        }
    }
    *buf = '\0';
    return totalRead;
}


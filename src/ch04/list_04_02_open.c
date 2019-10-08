//
// Created by 曹子钰 on 2019/10/5.
//
#include "tlpi_hdr.h"
#include <fcntl.h>

int main() {
    /* Open existing file for reading */

    int fd = open("startup", O_RDONLY);
    if (fd == -1) {
        errExit("open");
    }


    /* Open new or existing file for reading and writing, truncating to zero
    * bytes; file permissions read+write for owner, nothing for all others */

    int fd2 = open("myfile", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd2 == -1) {
        errExit("open");
    }

    /* Open new or existing file for writing;
     * writes should always append to end of file */

    int fd3 = open("w.log", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd3 == -1) {
        errExit("open");
    }

    return 0;
}
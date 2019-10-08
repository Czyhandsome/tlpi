//
// Created by 曹子钰 on 2019/10/5.
//
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
    /** check number of arguments or help **/

    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n", argv[0]);
    }

    /** open file **/

    /* rw-rw-rw- */
    int fd = open(argv[1], O_RDWR | O_CREAT,
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                  S_IROTH | S_IWOTH);

    if (fd == -1) {
        errExit("open");
    }

    size_t len;
    char *buf;
    ssize_t numRead;
    ssize_t numWritten;
    off_t offset;
    for (int ap = 2; ap < argc; ++ap) {
        switch (argv[ap][0]) {
            /* Display bytes at current offset, as text */
            case 'r':
            case 'R':
                len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
                buf = malloc(len);
                if (buf == NULL) {
                    errExit("malloc");
                }

                numRead = read(fd, buf, len);
                if (numRead == -1) {
                    errExit("read");
                }

                if (numRead == 0) {
                    printf("%s: end-of-file\n", argv[ap]);
                } else {
                    printf("%s: ", argv[ap]);
                    for (int j = 0; j < numRead; ++j) {
                        if (argv[ap][0] == 'r') {
                            printf("%c", isprint((unsigned char) buf[j] ?
                                                 buf[j] : '?'));
                        } else {
                            printf("%02x ", (unsigned int) buf[j]);
                        }
                    }
                    printf("\n");
                }
                free(buf);
                break;

                /* Write string at current offset */
            case 'w':
                numWritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
                if (numWritten == -1) {
                    errExit("write");
                }
                printf("%s: wrote %ld bytes\n", argv[ap], (long) numWritten);
                break;

                /* Change file offset */
            case 's':
                offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
                if (lseek(fd, offset, SEEK_SET) == -1) {
                    errExit("lseek");
                }
                printf("%s: seek succeeded\n", argv[ap]);
                break;

            default:
                cmdLineErr("Argument must start with [rRws]: %s\n", argv[ap]);
        }
    }

    return 0;
}
//
// Created by 曹子钰 on 2019/10/5.
//
#include "tlpi_hdr.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {

    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        usageErr("Usage: %s [-a] [files]\n", argv[0]);
    }

    int option;
    Boolean isAppend = FALSE;
    while ((option = getopt(argc, argv, ":a")) != -1) {
        switch (option) {
            case '?':
                printf("Unrecognized option -%c", option);
                usageErr("Usage: %s [-a] [files]\n", argv[0]);
            case 'a':
                isAppend = TRUE;
                break;
            default:
                fatal("Unexpected option in switch()");
                break;
        }
    }

    // The start index of files
    int start_index = optind;

    /* check if concat or trunc */
    int open_flags = O_WRONLY | O_CREAT;
    if (isAppend == TRUE) {
        // append
        open_flags |= O_APPEND;
    } else {
        // trunc
        open_flags |= O_TRUNC;
    }

    // Assign number of files
    const int NUM_FILES = argc - start_index;
    int fds[NUM_FILES + 1];

    // Set fds[0] as STDOUT_FILENO
    fds[0] = STDOUT_FILENO;
    /* open files */
    int num = 1;
    int i;
    for (i = start_index; i < argc; ++i) {
        const char *filename = argv[i];
        // open i-th file for write
        // -rw-rw-r--
        fds[num++] = open(filename, open_flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        if (fds[i] == -1) {
            errExit("opening file %s", filename);
        }
    }

    /* Read from stdin */
#define BUF_SIZE 20
    char buf[BUF_SIZE];
    ssize_t rd;
    while ((rd = read(STDIN_FILENO, buf, BUF_SIZE)) != 0) {
        if (rd == -1) {
            errExit("read from stdin");
        }
        // Write to all opened files
        for (i = 0; i < NUM_FILES + 1; ++i) {
            if (write(fds[i], buf, rd) != rd) {
                errExit("write to file[%d] fds[%d]", i, fds[i]);
            }
        }
    }

    // Close files except STDIN
    for (i = 1; i < NUM_FILES + 1; ++i) {
        if (close(fds[i]) == -1) {
            errExit("close file [%d]", fds[i]);
        }
    }

    return 0;
}

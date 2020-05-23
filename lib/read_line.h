//
// Created by 曹子钰 on 2020/5/23.
//

#ifndef LINUX_READ_LINE_H
#define LINUX_READ_LINE_H

#endif //LINUX_READ_LINE_H

#include "tlpi_hdr.h"

/*
 * Returns number of bytes copied into buffer (excluding
 * terminating null byte), or 0 on end-of-file, or –1 on error
 */
ssize_t read_line(int fd, void *buffer, size_t);
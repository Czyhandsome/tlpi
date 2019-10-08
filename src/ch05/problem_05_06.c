//
// Created by 曹子钰 on 2019/10/7.
//

#include <fcntl.h>
#include <tlpi_hdr.h>

int main() {
    const char *file = "problem_05_06.txt";
    int fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    int fd2 = dup(fd1);
    int fd3 = open(file, O_RDWR);
    write(fd1, "Hello,", 6);    // "Hello,"
    write(fd2, "world", 6);     // "Hello,world"
    lseek(fd2, 0, SEEK_SET);
    write(fd1, "HELLO,", 6);    // "HELLO,world"
    write(fd3, "Gidday", 6);    // "Giddayworld"
    return 0;
}
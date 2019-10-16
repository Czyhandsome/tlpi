//
// Created by 曹子钰 on 2019/10/10.
//

#include "tlpi_hdr.h"
#include "stdlib.h"

int main(int argc, char *argv[]) {
    struct Book {
        const char *name;
        int age;
    };

    struct Book *book = (struct Book *) calloc(sizeof(struct Book), 10);
    if (book == NULL) {
        errExit("calloc");
        return 1;
    }
    struct Book b;
    b.name = "abc";
    b.age = 3;
    book[1] = b;

    struct Book *nueva = (struct Book *) realloc(book, 1000);
    if (nueva == NULL) {
        errExit("realloc");
        return 1;
    }

    book = nueva;

    printf("name: %s, age: %d\n", book[1].name, book[1].age);

    free(book);

    return 0;
}
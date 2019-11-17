//
// Created by 曹子钰 on 2019/11/6.
//

#include "pthread.h"
#include "tlpi_hdr.h"

struct Input {
    int index;
    const char *val;
};

struct Output {
    int index;
    const char *retVal;
};

struct Input newInput(int index, const char *val) {
    struct Input i;
    i.index = index;
    i.val = val;
    return i;
}

void *worker(void *in) {
    struct Input *input = (struct Input *) in;
    printf("Hello (%d -> %s)\n", input->index, input->val);
    sleep(1);
    struct Output *output = malloc(sizeof(struct Output));
    if (output == NULL) {
        return NULL;
    }
    output->index = input->index;
    output->retVal = input->val;
    printf("Thread sleep over: (%d, %s)\n", output->index, output->retVal);
    return output;
}

int main(int argc, char *argv[]) {
    pthread_t thread;
    int s;
    struct Input *inputs = calloc(5, sizeof(struct Input));
    inputs[0] = newInput(1, "Hello!");
    inputs[1] = newInput(2, "Shoot!");
    inputs[1] = newInput(3, "Pero...");
    inputs[1] = newInput(4, "Escargo.");
    inputs[1] = newInput(5, "James");

    for (int i = 0; i < 5; ++i) {
        s = pthread_create(&thread, NULL, worker, (void *) &inputs[i]);
        if (s != 0) {
            errExitEN(s, "pthread_create");
        }
    }

    sleep(1);

    printf("Main sleep over!\n");
    exit(EXIT_SUCCESS);
}
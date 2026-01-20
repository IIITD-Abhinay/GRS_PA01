#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

/* Worker function declarations */
void cpu_worker(long count);
void mem_worker(long count);
void io_worker(long count);

typedef struct {
    char type[4];
    long count;
} thread_arg_t;

void* thread_runner(void *arg) {
    thread_arg_t *targ = (thread_arg_t *)arg;

    if (strcmp(targ->type, "cpu") == 0) {
        cpu_worker(targ->count);
    } else if (strcmp(targ->type, "mem") == 0) {
        mem_worker(targ->count);
    } else if (strcmp(targ->type, "io") == 0) {
        io_worker(targ->count);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <cpu|mem|io>\n", argv[0]);
        return 1;
    }

    pthread_t threads[2];
    thread_arg_t args[2];

    long count = 9 * 1000;

    for (int i = 0; i < 2; i++) {
        strcpy(args[i].type, argv[1]);
        args[i].count = count;
        pthread_create(&threads[i], NULL, thread_runner, &args[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

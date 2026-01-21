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

    if (argc != 3) {
        printf("Usage: %s <cpu|mem|io> <num_threads>\n", argv[0]);
        return 1;
    }

    char *type = argv[1];
    int num_threads = atoi(argv[2]);

    if (num_threads <= 0) {
        printf("Number of threads must be > 0\n");
        return 1;
    }

    pthread_t threads[num_threads];
    thread_arg_t args[num_threads];

    /* Roll number last digit = 0 → use 9 */
    long count = 9 * 1000;

    for (int i = 0; i < num_threads; i++) {
        strcpy(args[i].type, type);
        args[i].count = count;

        if (pthread_create(&threads[i], NULL, thread_runner, &args[i]) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

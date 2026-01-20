#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/* Worker function declarations */
void cpu_worker(long count);
void mem_worker(long count);
void io_worker(long count);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <cpu|mem|io>\n", argv[0]);
        return 1;
    }

    /* last digit of roll no = 0 → use 9 */
    long count = 9 * 1000;

    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            /* Child process */
            if (strcmp(argv[1], "cpu") == 0) {
                cpu_worker(count);
            } else if (strcmp(argv[1], "mem") == 0) {
                mem_worker(count);
            } else if (strcmp(argv[1], "io") == 0) {
                io_worker(count);
            } else {
                printf("Invalid worker type\n");
            }
            exit(0);
        }
    }

    /* Parent waits for children */
    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }

    return 0;
}

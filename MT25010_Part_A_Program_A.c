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

    if (argc != 3) {
        printf("Usage: %s <cpu|mem|io> <num_processes>\n", argv[0]);
        return 1;
    }

    char *type = argv[1];
    int num_processes = atoi(argv[2]);

    if (num_processes <= 0) {
        printf("Number of processes must be > 0\n");
        return 1;
    }

    /* Roll number last digit = 0 → use 9 */
    long count = 9 * 1000;

    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0) {
            /* Child process executes worker */
            if (strcmp(type, "cpu") == 0) {
                cpu_worker(count);
            } else if (strcmp(type, "mem") == 0) {
                mem_worker(count);
            } else if (strcmp(type, "io") == 0) {
                io_worker(count);
            } else {
                printf("Invalid worker type\n");
            }
            exit(0);
        }
    }

    /* Parent waits for all child processes */
    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    return 0;
}

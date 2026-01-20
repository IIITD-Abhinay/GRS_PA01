#include <stdlib.h>

void mem_worker(long count) {
    long size = count * 100;
    int *arr = (int *)malloc(size * sizeof(int));

    for (long i = 0; i < size; i++) {
        arr[i] = i;
    }

    for (long i = 0; i < size; i++) {
        arr[i] += 1;
    }

    free(arr);
}

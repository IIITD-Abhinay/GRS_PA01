#include <math.h>

void cpu_worker(long count) {
    volatile double x = 0;
    for (long i = 0; i < count; i++) {
        x += sqrt(i) * sqrt(i + 1);
    }
}

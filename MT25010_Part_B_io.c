#include <fcntl.h>
#include <unistd.h>

void io_worker(long count) {
    int fd = open("temp_io.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    char buf = 'A';

    for (long i = 0; i < count; i++) {
        write(fd, &buf, 1);
    }

    close(fd);
}

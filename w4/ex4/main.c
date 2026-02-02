#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(void) {
    char buffer[1];

    int fd = open("output.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        _exit(1);
    }

    ssize_t bytes_read = read(fd, buffer, 1);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        _exit(1);
    }

    if (bytes_read == 0) {
        printf("File is empty\n");
        close(fd);
        _exit(1);
    }

    printf("Read character: '%c'\n", buffer[0]);

    if (close(fd) == -1) {
        perror("close");
        _exit(1);
    }

    return 0;
}

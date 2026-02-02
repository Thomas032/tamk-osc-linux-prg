#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

int main(void) {
    char ch;

    printf("Enter a single character: ");
    if (scanf(" %c", &ch) != 1) {
        printf("Failed to read character\n");
        _exit(1);
    }

    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        _exit(1);
    }

    ssize_t written = write(fd, &ch, 1);
    if (written != 1) {
        perror("write");
        close(fd);
        _exit(1);
    }

    if (close(fd) == -1) {
        perror("close");
        _exit(1);
    }

    printf("Successfully wrote one byte to output.txt\n");
    return 0;
}

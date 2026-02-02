#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(void){
    const char *path = "/tmp/does_not_exist.txt";

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        int err = errno;

        printf("open(\"%s\") failed\n", path);
        printf("errno = %d\n", err);
        printf("strerror(errno): %s\n", strerror(err));

        errno = err;
        perror("perror");

        return 1;
    }

    close(fd);
    return 0;
}
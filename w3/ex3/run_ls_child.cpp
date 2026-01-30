#include <cerrno>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(){
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed: " << std::strerror(errno) << "\n";
        return 1;
    }

    if(pid == 0){
        const char* path = "/bin/ls";
        char* args[] = {
            const_cast<char*>("ls"),
            nullptr
        };

        execve(path, const_cast<char* const*>(args), environ);

        std::cerr << "execve failed: " << std::strerror(errno) << "\n";
        _exit(127);
    }

    int status = 0;
    if (waitpid(pid, &status, 0) < 0) {
        std::cerr << "waitpid failed: " << std::strerror(errno) << "\n";
        return 1;
    }

    return 0;
}
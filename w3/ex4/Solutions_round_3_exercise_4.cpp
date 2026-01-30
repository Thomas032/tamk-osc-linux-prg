#include <cerrno>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command> [args...]\n";
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "fork failed: " << std::strerror(errno) << "\n";
        return 1;
    }

    if (pid == 0) {

        std::string path = "/bin/";
        path += argv[1];

        char** exec_argv = &argv[1];

        execve(path.c_str(), exec_argv, environ);

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

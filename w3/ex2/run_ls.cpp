#include <cerrno>
#include <cstring>
#include <iostream>
#include <unistd.h>

extern char **environ;

int main(){
    const char* path = "/bin/ls";

    char* const args[] = {const_cast<char*>("ls"), nullptr};

    execve(path, args, environ);
    std::cerr << "execve failed: " << std::strerror(errno) << "\n";

    return 1;
}
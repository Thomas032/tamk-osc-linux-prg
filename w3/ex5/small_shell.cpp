#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

// Helper function to check if a file exists and is executable
bool is_executable(const std::string& path) {
    struct stat sb;
    return (stat(path.c_str(), &sb) == 0 && (sb.st_mode & S_IXUSR));
}

std::string find_command(const std::string& cmd) {
    if (cmd.find('/') != std::string::npos) {
        return cmd;
    }
    
    const char* search_paths[] = {
        "/bin/",
        "/usr/bin/",
        "/usr/local/bin/",
        nullptr
    };
    
    for (int i = 0; search_paths[i] != nullptr; i++) {
        std::string full_path = search_paths[i] + cmd;
        if (is_executable(full_path)) {
            return full_path;
        }
    }
    
    return cmd;
}

void type_prompt() {
    std::cout << "Enter a command: ";
    std::cout.flush();
}

bool read_command(std::string& command, std::vector<std::string>& args) {
    std::string line;
    if (!std::getline(std::cin, line)) {
        return false;
    }
    
    size_t start = line.find_first_not_of(" \t");
    if (start == std::string::npos) {
        command.clear();
        args.clear();
        return true;
    }
    
    line = line.substr(start);
    
    std::istringstream iss(line);
    args.clear();
    std::string token;
    
    while (iss >> token) {
        args.push_back(token);
    }
    
    if (args.empty()) {
        command.clear();
        return true;
    }
    
    command = args[0];
    return true;
}

void execute(const std::string& command, const std::vector<std::string>& args) {
    std::string full_path = find_command(command);
    
    pid_t pid = fork();
    
    if (pid < 0) {
        std::cerr << "fork failed: " << std::strerror(errno) << "\n";
        return;
    }
    
    if (pid == 0) {
        char** exec_argv = new char*[args.size() + 1];
        for (size_t i = 0; i < args.size(); i++) {
            exec_argv[i] = const_cast<char*>(args[i].c_str());
        }
        exec_argv[args.size()] = nullptr;
        
        execve(full_path.c_str(), exec_argv, environ);
        
        std::cerr << "execve failed: " << std::strerror(errno) << "\n";
        delete[] exec_argv;
        _exit(127);
    }
    
    int status = 0;
    if (waitpid(pid, &status, 0) < 0) {
        std::cerr << "waitpid failed: " << std::strerror(errno) << "\n";
    }
}

int main() {
    std::string command;
    std::vector<std::string> args;
    
    while (true) {
        type_prompt();
        
        if (!read_command(command, args)) {
            break;
        }
        
        if (command.empty()) {
            break;
        }
        
        execute(command, args);
    }
    
    return 0;
}

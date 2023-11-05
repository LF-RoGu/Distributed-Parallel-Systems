#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <chrono>

int main() {
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == 0) {
        // This code is executed by the child process
        std::cout << "Child process is running." << std::endl;
    } else if (child_pid > 0) {
        // This code is executed by the parent process
        std::cout << "Parent process is running." << std::endl;
    } else {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    return 0;
}

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid > 0) {
        std::cout << "printed from parent process " << getpid() << std::endl;
        wait(nullptr);
    } else {
        std::cout << "printed from child process " << getpid() << std::endl;
        exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
    int status;
    char *const argv1[] = {"./print", "1", NULL};
    char *const argv2[] = {"./print", "2", NULL};
    char *const argv3[] = {"./print", "3", NULL};
    char *const argv4[] = {"./print", "4", NULL};

    pid_t pid[3];

    pid[0] = fork();
    if (pid[0] == 0) {
        execvp(argv1[0], argv1);
        // 根据 execvp 的行为，以下语句不会被执行
        sleep(1);
        execvp(argv2[0], argv2);
        sleep(1);
    }

    pid[1] = fork();
    if (pid[1] == 0) {
        execvp(argv3[0], argv3);
        sleep(1);
    }

    pid[2] = fork();
    if (pid[2] == 0) {
        execvp(argv4[0], argv4);
        sleep(1);
    }

    wait(&status);
    wait(&status);
    wait(&status);

    printf("Main process finished.\n");
}

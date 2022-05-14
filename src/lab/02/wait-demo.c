#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COUNT   100
#define BUF_SIZE    100

void ChildProcess(char[], char[]); /* child process declare */

int main(void)
{
    pid_t     pid1, pid2, pid;
    int       status;
    int       i;
    char      buf[BUF_SIZE];

    printf("*** Parent is about to fork process 1 ***\n");

    pid1 = fork();
    if (pid1 < 0) {
        printf("Failed to fork process 1\n");
        return 1;
    } else if (pid1 == 0) {  /* In Child Process */
        ChildProcess("First", "   ");
        return 0;
    }

    printf("*** Parent is about to fork process 2 ***\n");

    pid2 = fork();
    if (pid2 < 0) {
        printf("Failed to fork process 2\n");
        return 1;
    } else if (pid2 == 0) {
        ChildProcess("Second", "      ");
        return 0;
    }

    /* The parent process can do something else. */

    sprintf(buf, "*** Parent enters waiting status .....\n");
    write(1, buf, strlen(buf));

    pid = wait(&status);
    sprintf(buf, "*** Parent detects process %d was done ***\n", pid);
    write(1, buf, strlen(buf));

    pid = wait(&status);
    printf("*** Parent detects process %d is done ***\n", pid);

    printf("*** Parent exits ***\n");
    return 0;
}

/* Child Process's Code */
void ChildProcess(char *number, char *space)
{
    pid_t pid;
    int i;
    char buf[BUF_SIZE];

    pid = getpid();
    sprintf(buf, "%s%s child process starts (pid = %d)\n",
           space, number, pid);
    write(1, buf, strlen(buf));

    for (i = 1; i <= MAX_COUNT; i++) {
        sprintf(buf, "%s%s child's output, value = %d\n", space, number, i);
        write(1, buf, strlen(buf));
    }

    sprintf(buf, "%s%s child (pid = %d) is about to exit\n",
           space, number, pid);
    write(1, buf, strlen(buf));
}

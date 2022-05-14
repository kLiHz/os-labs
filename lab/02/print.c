#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    printf("Process %s has start!\n", argv[1]);
    sleep(3);
    printf("Process %s finished!\n", argv[1]);
    return 0;
}

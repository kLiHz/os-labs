#include "functions.h"
#include "stdio.h"

int main() {
    printf("Welcome, Henry.\n");
    int x1 = 5;
    int x2 = 6;
    int x3 = 7;
    printf("The result of f(%d) is %d.\n", x1, f(x1));
    printf("The result of f(%d) is %d.\n", x2, f(x2));
    printf("The result of f(%d) is %d.\n", x3, f(x3));
    return 0;
}
